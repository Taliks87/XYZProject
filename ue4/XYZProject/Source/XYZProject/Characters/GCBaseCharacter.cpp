// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacter.h"

#include "DisplayDebugHelpers.h"
#include "GeneratedCodeHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "XYZProject/Components/MovementComponents/GCBaseCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacter, Log, All);

AGCBaseCharacter::AGCBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGCBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	GCBaseCharacterMovementComponent = StaticCast<UGCBaseCharacterMovementComponent*>(GetCharacterMovement());
	IKScale = GetActorScale3D().Z;    
	IKTraceDistance = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

void AGCBaseCharacter::ChangeCrouchState()
{
		if(bIsCrouching)
		{
			UnCrouch();
		}
		else
		{
			Crouch();
		}
 }

void AGCBaseCharacter::ChangeProneState()
{
	bool bProning = GCBaseCharacterMovementComponent->IsProning();
	if(bProning)
	{
		UnProne();
	}
	else
	{
		if(!GetCharacterMovement()->CanEverCrouch() || GetCharacterMovement()->IsCrouching())
		{
			Prone();
		}
	}
}

void AGCBaseCharacter::StartSprint()
{
	bIsSprintRequested = true;
	if (bIsCrouched)
	{
		UnCrouch();
	}
}

void AGCBaseCharacter::StopSprint()
{
	bIsSprintRequested = false;
}

void AGCBaseCharacter::Jump()
{
	if(bIsProned)
	{
		UnProne();
		UnCrouch();
	}
	else
	{
		Super::Jump();
	}
}

void AGCBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	IKRightFootOffset = FMath::FInterpTo(IKRightFootOffset, GetIKOffsetForASocket(RightFootSocketName), DeltaTime, IKInterpSpeed);
	IKLeftFootOffset = FMath::FInterpTo(IKLeftFootOffset, GetIKOffsetForASocket(LeftFootSocketName), DeltaTime, IKInterpSpeed);

	RefreshStamina(DeltaTime);
	if(CurrentStamina != MaxStamina && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Stamina: %.2f"), CurrentStamina));	
	}
}

void AGCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
}

void AGCBaseCharacter::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	if (GCBaseCharacterMovementComponent)
	{
		if (CanCrouch())
		{
			GCBaseCharacterMovementComponent->bWantsToProne = false;
		}
	}
}

void AGCBaseCharacter::OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();
	RecalculateMashOffset(-HeightAdjust, ScaledHeightAdjust);
}

void AGCBaseCharacter::OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();
	RecalculateMashOffset(HeightAdjust, ScaledHeightAdjust);
}

void AGCBaseCharacter::OnEndProne(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();
	RecalculateMashOffset(-HeightAdjust, ScaledHeightAdjust);	
}

void AGCBaseCharacter::OnStartProne(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();
	RecalculateMashOffset(HeightAdjust, ScaledHeightAdjust);
}

void AGCBaseCharacter::Prone(bool bClientSimulation)
{
	if (GCBaseCharacterMovementComponent)
	{
		if (CanProne())
		{
			GCBaseCharacterMovementComponent->bWantsToProne = true;
			GCBaseCharacterMovementComponent->bWantsToCrouch = false;
		}
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		else if (!GCBaseCharacterMovementComponent->CanEverProne())
		{
			UE_LOG(LogCharacter, Log, TEXT("%s is trying to prone, but proning is disabled on this character! (check CharacterMovement NavAgentSettings)"), *GetName());
		}
#endif
	}
}

void AGCBaseCharacter::UnProne(bool bClientSimulation)
{
	if (GCBaseCharacterMovementComponent)
	{
		GCBaseCharacterMovementComponent->bWantsToProne = false;
		GCBaseCharacterMovementComponent->bWantsToCrouch = true;
	}
}

bool AGCBaseCharacter::CanProne() const
{
	return bIsCrouched && !bIsProned && GCBaseCharacterMovementComponent && GCBaseCharacterMovementComponent->CanEverProne() && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void AGCBaseCharacter::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
	static FName NAME_Physics = FName(TEXT("Physics"));
	if (DebugDisplay.IsDisplayOn(NAME_Physics) )
	{
		float Indent = 0.f;
		FIndenter PhysicsIndent(Indent);
		FDisplayDebugManager& DisplayDebugManager = Canvas->DisplayDebugManager;
		const bool Crouched = GCBaseCharacterMovementComponent && GCBaseCharacterMovementComponent->IsProning();
		FString T = FString::Printf(TEXT("Crouched %i"), Crouched);
		DisplayDebugManager.DrawString(T, Indent);
	}
}

bool AGCBaseCharacter::CanSprint() const
{
	return !bIsProned;
}

bool AGCBaseCharacter::CanJumpInternal_Implementation() const
{
	if(bIsProned)
	{
		return false;
	}
	return Super::CanJumpInternal_Implementation();
}

float AGCBaseCharacter::GetIKOffsetForASocket(const FName& SocketName) const
{
	float Result = 0.0f;
    
	const FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
	const FVector TraceStart(SocketLocation.X, SocketLocation.Y, GetActorLocation().Z);
	const FVector TraceEnd = TraceStart - (IKTraceDistance + IKTraceExtendDistance) * FVector::UpVector;
    
	FHitResult HitResult;
	const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, TraceType, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
	 	Result = (TraceEnd.Z - HitResult.Location.Z) / IKScale + IKTraceExtendDistance;
	}
	return Result;
}

void AGCBaseCharacter::RefreshStamina(float DeltaTime)
{
	const bool IsSprinting = GCBaseCharacterMovementComponent->IsSprinting();
	if (IsSprinting)
	{
		CurrentStamina -= SprintStaminaConsumptionVelocity * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		if(CurrentStamina == 0.0f)
		{
			GCBaseCharacterMovementComponent->SetIsOutOfStamina(true);
		}
		if(!bIsSprintRequested)
		{
			GCBaseCharacterMovementComponent->StopSprint();
			OnSprintEnd();
		}
	} else {
		CurrentStamina += StaminaRestoreVelocity * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		if(CurrentStamina == MaxStamina)
		{
			GCBaseCharacterMovementComponent->SetIsOutOfStamina(false);
		}
		if(bIsSprintRequested && CanSprint())
		{
			GCBaseCharacterMovementComponent->StartSprint();
			OnSprintStart();
		}
		if(!bIsSprintRequested)
		{
			GCBaseCharacterMovementComponent->StopSprint();
			OnSprintEnd();
		}
	}
}

void AGCBaseCharacter::RecalculateMashOffset(float HeightAdjust, float ScaledHeightAdjust)
{
	const AGCBaseCharacter* DefaultChar = GetDefault<AGCBaseCharacter>(GetClass());
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	if (CharacterMesh)
	{
		BaseTranslationOffset.Z = CharacterMesh->GetRelativeLocation().Z + HeightAdjust;
		FVector DeltaLocation = FVector::UpVector * HeightAdjust;
		//TODO: Fix magic bug!!!!
		CharacterMesh->SetRelativeLocationAndRotation(CharacterMesh->GetRelativeLocation() + DeltaLocation,
			CharacterMesh->GetRelativeRotation());
	}
	else
	{
		BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z + HeightAdjust;
	}
}
