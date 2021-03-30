// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacterMovementComponent.h"


#include "Components/CapsuleComponent.h"
#include "XYZProject/Characters/GCBaseCharacter.h"

void UGCBaseCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf( !bCanProne || ProneCapsuleRadius <= ProneCapsuleHalfHeight, TEXT("UGCBaseCharacterMovementComponent::BeginPlay Capsule radius must be less then hlaf hight"));
}

void UGCBaseCharacterMovementComponent::PostLoad()
{
	Super::PostLoad();
	GCBaseCharacterOwner = Cast<AGCBaseCharacter>(PawnOwner);
}

void UGCBaseCharacterMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	Super::SetUpdatedComponent(NewUpdatedComponent);
	GCBaseCharacterOwner = Cast<AGCBaseCharacter>(PawnOwner);
}

float UGCBaseCharacterMovementComponent::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();
	if(bIsSprinting)
	{
		Result = SprintSpeed;
	}
	else if(bIsOutOfStamina)
	{
		Result = OutOfStaminaSpeed;
	}
	else if(IsProning())
	{
		Result = MaxProneSpeed;
	}
	return Result;
}

bool UGCBaseCharacterMovementComponent::CanAttemptJump() const
{
	return Super::CanAttemptJump() && !bIsOutOfStamina;
}

void UGCBaseCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{	
	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		// Check for a change stand/crouch/prone state.
		const bool bCrouching = IsCrouching();
		const bool bProning = IsProning();
		const bool bStanding = !bProning && !bCrouching;
		const bool bWantToStand = !bWantsToCrouch && !bWantsToProne;
		if (bCrouching && (bWantToStand || !CanCrouchInCurrentState()))
		{
			UnCrouch(false);
		}
		else if (bStanding && bWantsToCrouch && CanCrouchInCurrentState())
		{
			Crouch(false);
		}
		else if (bProning && (bWantsToCrouch || bWantToStand || !CanProneInCurrentState()))
		{
			ProneToCrouch(false);
		}
		else if (bCrouching && bWantsToProne && CanProneInCurrentState())
		{
			CrouchToProne(false);
		}
	}
}

void UGCBaseCharacterMovementComponent::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
}

void UGCBaseCharacterMovementComponent::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
}

void UGCBaseCharacterMovementComponent::CrouchToProne(bool bClientSimulation)
{
	if (!HasValidData())
	{
		return;
	}
	
	if (!bClientSimulation && !CanProneInCurrentState())
	{
		return;
	}

	// See if collision is already at desired size.
	if (GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() == ProneCapsuleHalfHeight
		&& GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius() == ProneCapsuleRadius)
	{
		if (!bClientSimulation)
		{
			GCBaseCharacterOwner->bIsCrouched = false;
			GCBaseCharacterOwner->bIsProned = true;			
		}
		GCBaseCharacterOwner->OnStartProne( 0.f, 0.f );
		return;
	}

	if (bClientSimulation && CharacterOwner->GetLocalRole() == ROLE_SimulatedProxy)
	{
		// restore collision size before proning
		
		ACharacter* DefaultCharacter = GCBaseCharacterOwner->GetClass()->GetDefaultObject<ACharacter>();
		GCBaseCharacterOwner->GetCapsuleComponent()->SetCapsuleSize(		
			DefaultCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius(),
			CrouchedHalfHeight);
		bShrinkProxyCapsule = true;
	}

	// Change collision size to proning dimensions
	const float ComponentScale = GCBaseCharacterOwner->GetCapsuleComponent()->GetShapeScale();
	const float OldUnscaledHalfHeight = GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	const float OldUnscaledRadius = GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius();	
	GCBaseCharacterOwner->GetCapsuleComponent()->SetCapsuleSize(ProneCapsuleRadius, ProneCapsuleHalfHeight);
	float HalfHeightAdjust = (OldUnscaledHalfHeight - ProneCapsuleHalfHeight);
	float ScaledHalfHeightAdjust = HalfHeightAdjust * ComponentScale;

	if( !bClientSimulation )
	{
		// Proning to a larger height? (this is rare)
		if (ProneCapsuleHalfHeight > OldUnscaledHalfHeight)
		{
			FCollisionQueryParams CapsuleParams(SCENE_QUERY_STAT(ProneTrace), false, GCBaseCharacterOwner);
			FCollisionResponseParams ResponseParam;
			InitCollisionParams(CapsuleParams, ResponseParam);
			const bool bEncroached = GetWorld()->OverlapBlockingTestByChannel(UpdatedComponent->GetComponentLocation() - FVector(0.f,0.f,ScaledHalfHeightAdjust), FQuat::Identity,
                UpdatedComponent->GetCollisionObjectType(), GetPawnCapsuleCollisionShape(SHRINK_None), CapsuleParams, ResponseParam);

			// If encroached, cancel
			if( bEncroached )
			{
				GCBaseCharacterOwner->GetCapsuleComponent()->SetCapsuleSize(OldUnscaledRadius, OldUnscaledHalfHeight);
				return;
			}
		}
		bProneMaintainsBaseLocation = bCrouchMaintainsBaseLocation;
		if (bProneMaintainsBaseLocation)
		{
			// Intentionally not using MoveUpdatedComponent, where a horizontal plane constraint would prevent the base of the capsule from staying at the same spot.
			UpdatedComponent->MoveComponent(FVector(0.f, 0.f, -ScaledHalfHeightAdjust), UpdatedComponent->GetComponentQuat(), true, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);
		}

		GCBaseCharacterOwner->bIsCrouched = false;
		GCBaseCharacterOwner->bIsProned = true;
	}
	
	bForceNextFloorCheck = true;

	// OnStartProne takes the change from the Default size, not the current one (though they are usually the same).
	const float MeshAdjust = ScaledHalfHeightAdjust;
	AGCBaseCharacter* DefaultCharacter = GCBaseCharacterOwner->GetClass()->GetDefaultObject<AGCBaseCharacter>();
	HalfHeightAdjust = (DefaultCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() - ProneCapsuleHalfHeight);
	ScaledHalfHeightAdjust = HalfHeightAdjust * ComponentScale;

	AdjustProxyCapsuleSize();
	GCBaseCharacterOwner->OnStartProne( HalfHeightAdjust, ScaledHalfHeightAdjust );

	// Don't smooth this change in mesh position
	if ((bClientSimulation && GCBaseCharacterOwner->GetLocalRole() == ROLE_SimulatedProxy) || (IsNetMode(NM_ListenServer) && GCBaseCharacterOwner->GetRemoteRole() == ROLE_AutonomousProxy))
	{
		FNetworkPredictionData_Client_Character* ClientData = GetPredictionData_Client_Character();
		if (ClientData)
		{
			ClientData->MeshTranslationOffset -= FVector(0.f, 0.f, MeshAdjust);
			ClientData->OriginalMeshTranslationOffset = ClientData->MeshTranslationOffset;
		}
	}
}

void UGCBaseCharacterMovementComponent::ProneToCrouch(bool bClientSimulation)
{
	if (!HasValidData())
	{
		return;
	}

	AGCBaseCharacter* DefaultCharacter = GCBaseCharacterOwner->GetClass()->GetDefaultObject<AGCBaseCharacter>();

	// See if collision is already at desired size.
	if( GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() == CrouchedHalfHeight )
	{
		if (!bClientSimulation)
		{
			GCBaseCharacterOwner->bIsProned = false;
			GCBaseCharacterOwner->bIsCrouched = true;
		}
		GCBaseCharacterOwner->OnEndProne( 0.f, 0.f );
		return;
	}

	const float CurrentProneHalfHeight = GCBaseCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	const float ComponentScale = GCBaseCharacterOwner->GetCapsuleComponent()->GetShapeScale();
	const float OldUnscaledHalfHeight = GCBaseCharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	const float HalfHeightAdjust = CrouchedHalfHeight - OldUnscaledHalfHeight;
	const float ScaledHalfHeightAdjust = HalfHeightAdjust * ComponentScale;
	const FVector PawnLocation = UpdatedComponent->GetComponentLocation();

	// Grow to unproned size.
	check(GCBaseCharacterOwner->GetCapsuleComponent());

	if( !bClientSimulation )
	{
		// Try to stay in place and see if the larger capsule fits. We use a slightly taller capsule to avoid penetration.
		const UWorld* MyWorld = GetWorld();
		const float SweepInflation = KINDA_SMALL_NUMBER * 10.f;
		FCollisionQueryParams CapsuleParams(SCENE_QUERY_STAT(ProneTrace), false, GCBaseCharacterOwner);
		FCollisionResponseParams ResponseParam;
		InitCollisionParams(CapsuleParams, ResponseParam);

		// Compensate for the difference between current capsule size and crouching size
		const FCollisionShape CrouchingCapsuleShape = GetPawnCapsuleCollisionShape(SHRINK_AllCustom, -SweepInflation - ScaledHalfHeightAdjust); // Shrink by negative amount, so actually grow it.
		const ECollisionChannel CollisionChannel = UpdatedComponent->GetCollisionObjectType();
		bool bEncroached = true;
		
		bProneMaintainsBaseLocation = bCrouchMaintainsBaseLocation;
		if (!bProneMaintainsBaseLocation)
		{
			// Expand in place
			bEncroached = MyWorld->OverlapBlockingTestByChannel(PawnLocation, FQuat::Identity, CollisionChannel, CrouchingCapsuleShape, CapsuleParams, ResponseParam);
		
			if (bEncroached)
			{
				// Try adjusting capsule position to see if we can avoid encroachment.
				if (ScaledHalfHeightAdjust > 0.f)
				{
					// Shrink to a short capsule, sweep down to base to find where that would hit something, and then try to crouch from there.
					float PawnRadius, PawnHalfHeight;
					GCBaseCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleSize(PawnRadius, PawnHalfHeight);
					const float ShrinkHalfHeight = PawnHalfHeight - PawnRadius;
					const float TraceDist = PawnHalfHeight - ShrinkHalfHeight;
					const FVector Down = FVector(0.f, 0.f, -TraceDist);

					FHitResult Hit(1.f);
					const FCollisionShape ShortCapsuleShape = GetPawnCapsuleCollisionShape(SHRINK_AllCustom, ShrinkHalfHeight);
					const bool bBlockingHit = MyWorld->SweepSingleByChannel(Hit, PawnLocation, PawnLocation + Down, FQuat::Identity, CollisionChannel, ShortCapsuleShape, CapsuleParams);
					if (Hit.bStartPenetrating)
					{
						bEncroached = true;
					}
					else
					{
						// Compute where the base of the sweep ended up, and see if we can crouch there
						const float DistanceToBase = (Hit.Time * TraceDist) + ShortCapsuleShape.Capsule.HalfHeight;
						const FVector NewLoc = FVector(PawnLocation.X, PawnLocation.Y, PawnLocation.Z - DistanceToBase + CrouchingCapsuleShape.Capsule.HalfHeight + SweepInflation + MIN_FLOOR_DIST / 2.f);
						bEncroached = MyWorld->OverlapBlockingTestByChannel(NewLoc, FQuat::Identity, CollisionChannel, CrouchingCapsuleShape, CapsuleParams, ResponseParam);
						if (!bEncroached)
						{
							// Intentionally not using MoveUpdatedComponent, where a horizontal plane constraint would prevent the base of the capsule from staying at the same spot.
							UpdatedComponent->MoveComponent(NewLoc - PawnLocation, UpdatedComponent->GetComponentQuat(), false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);
						}
					}
				}
			}
		}
		else
		{
			// Expand while keeping base location the same.
			FVector CrouchingLocation = PawnLocation + FVector(0.f, 0.f, CrouchingCapsuleShape.GetCapsuleHalfHeight() - CurrentProneHalfHeight);
			bEncroached = MyWorld->OverlapBlockingTestByChannel(CrouchingLocation, FQuat::Identity, CollisionChannel, CrouchingCapsuleShape, CapsuleParams, ResponseParam);

			if (bEncroached)
			{
				if (IsMovingOnGround())
				{
					// Something might be just barely overhead, try moving down closer to the floor to avoid it.
					const float MinFloorDist = KINDA_SMALL_NUMBER * 10.f;
					if (CurrentFloor.bBlockingHit && CurrentFloor.FloorDist > MinFloorDist)
					{
						CrouchingLocation.Z -= CurrentFloor.FloorDist - MinFloorDist;
						bEncroached = MyWorld->OverlapBlockingTestByChannel(CrouchingLocation, FQuat::Identity, CollisionChannel, CrouchingCapsuleShape, CapsuleParams, ResponseParam);
					}
				}
			}

			if (!bEncroached)
			{
				// Commit the change in location.
				UpdatedComponent->MoveComponent(CrouchingLocation - PawnLocation, UpdatedComponent->GetComponentQuat(), false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);
				bForceNextFloorCheck = true;
			}
		}

		// If still encroached then abort.
		if (bEncroached)
		{
			return;
		}

		GCBaseCharacterOwner->bIsProned = false;
		GCBaseCharacterOwner->bIsCrouched = true;
	}	
	else
	{
		bShrinkProxyCapsule = true;
	}

	// Now call SetCapsuleSize() to cause touch/untouch events and actually grow the capsule
	GCBaseCharacterOwner->GetCapsuleComponent()->SetCapsuleSize(DefaultCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius(), CrouchedHalfHeight, true);

	const float MeshAdjust = ScaledHalfHeightAdjust;
	AdjustProxyCapsuleSize();
	GCBaseCharacterOwner->OnEndProne( HalfHeightAdjust, ScaledHalfHeightAdjust );

	// Don't smooth this change in mesh position
	if ((bClientSimulation && GCBaseCharacterOwner->GetLocalRole() == ROLE_SimulatedProxy) || (IsNetMode(NM_ListenServer) && GCBaseCharacterOwner->GetRemoteRole() == ROLE_AutonomousProxy))
	{
		FNetworkPredictionData_Client_Character* ClientData = GetPredictionData_Client_Character();
		if (ClientData)
		{
			ClientData->MeshTranslationOffset += FVector(0.f, 0.f, MeshAdjust);
			ClientData->OriginalMeshTranslationOffset = ClientData->MeshTranslationOffset;
		}
	}
}

bool UGCBaseCharacterMovementComponent::IsProning() const
{
	return GCBaseCharacterOwner && GCBaseCharacterOwner->bIsProned;
}

void UGCBaseCharacterMovementComponent::StartSprint()
{
	if(!bIsOutOfStamina)
	{
		bIsSprinting = true;
		bForceMaxAccel = 1;	
	}	
}

void UGCBaseCharacterMovementComponent::StopSprint()
{
	bIsSprinting = false;
	bForceMaxAccel = 0;
}

void UGCBaseCharacterMovementComponent::SetIsOutOfStamina(bool bIsOutOfStamina_In)
{
	bIsOutOfStamina = bIsOutOfStamina_In;
	if(bIsOutOfStamina)
	{
		StopSprint();
	}
}

bool UGCBaseCharacterMovementComponent::CanProneInCurrentState() const
{
	if (!CanEverProne())
	{
		return false;
	}

	return CanCrouchInCurrentState() || IsCrouching();
}
