// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacter.h"

#include "GeneratedCodeHelpers.h"
#include "Components/CapsuleComponent.h"
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

void AGCBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION( AGCBaseCharacter, bIsProned, COND_SimulatedOnly );
}

void AGCBaseCharacter::ChangeCrouchState()
{
	const bool bCanEverProne = GCBaseCharacterMovementComponent->CanEverProne();
	const bool bIsCrouching = GetCharacterMovement()->IsCrouching();
	if(bCanEverProne)
	{
		if ( GCBaseCharacterMovementComponent->IsProning() || !bIsCrouching ) 
		{		
			Crouch();		
		}	
	} else {
		if(bIsCrouching)
		{
			Crouch();		
		} else {
			UnCrouch();
		}	 
	}
}

void AGCBaseCharacter::ChangeProneState()
{
	if(GCBaseCharacterMovementComponent->IsProning())
	{
		UnProne();
		return;
	}
	if(GetCharacterMovement()->CanEverCrouch() && GetCharacterMovement()->IsCrouching())
	{		
		Prone();						
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

void AGCBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	IKRightFootOffset = FMath::FInterpTo(IKRightFootOffset, GetIKOffsetForASocket(RightFootSocketName), DeltaTime, IKInterpSpeed);
	IKLeftFootOffset = FMath::FInterpTo(IKLeftFootOffset, GetIKOffsetForASocket(LeftFootSocketName), DeltaTime, IKInterpSpeed);

	if(!GCBaseCharacterMovementComponent->IsSprinting())
	{
		CurrentStamina += StaminaRestoreVelocity * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		if(CurrentStamina == MaxStamina)
		{
			GCBaseCharacterMovementComponent->SetIsOutOfStamina(false);
		}				
	}
	TryChangeSprintState(DeltaTime);
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

void AGCBaseCharacter::OnRep_IsProned()
{
	if (GCBaseCharacterMovementComponent)
	{
		if (bIsProned)
		{
			GCBaseCharacterMovementComponent->bWantsToCrouch = true;
			GCBaseCharacterMovementComponent->Prone(true);
		}
		else
		{
			GCBaseCharacterMovementComponent->bWantsToCrouch = false;
			GCBaseCharacterMovementComponent->UnProne(true);
		}
		GCBaseCharacterMovementComponent->bNetworkUpdateReceived = true;
	}
}

void AGCBaseCharacter::OnEndProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
}

void AGCBaseCharacter::OnStartProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
}

void AGCBaseCharacter::Prone(bool bClientSimulation)
{
	if (GCBaseCharacterMovementComponent)
	{
		if (CanProne())
		{
			GCBaseCharacterMovementComponent->bWantsToProne = true;
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
	}
}

bool AGCBaseCharacter::CanProne() const
{
	return bIsCrouched && !bIsProned && GCBaseCharacterMovementComponent && GCBaseCharacterMovementComponent->CanEverProne() && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

bool AGCBaseCharacter::CanSprint() const
{
	return true;
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

void AGCBaseCharacter::TryChangeSprintState(float DeltaTime)
{
	const bool IsSprinting = GCBaseCharacterMovementComponent->IsSprinting();
	if(bIsSprintRequested && !IsSprinting && CanSprint())
	{
		GCBaseCharacterMovementComponent->StartSprint();
		OnSprintStart();
	}	
	
	if (IsSprinting)
	{
		if(!bIsSprintRequested)
		{
			GCBaseCharacterMovementComponent->StopSprint();
			OnSprintEnd();
		}	
		CurrentStamina -= SprintStaminaConsumptionVelocity * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);		
		if(CurrentStamina == 0.0f)
		{
			GCBaseCharacterMovementComponent->SetIsOutOfStamina(true);
		}
	}	
}
