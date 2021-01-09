// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacter.h"


#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "XYZProject/Components/MovementComponents/GCBaseCharacterMovementComponent.h"


AGCBaseCharacter::AGCBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGCBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	GCBaseCharacterMovementComponent = StaticCast<UGCBaseCharacterMovementComponent*>(GetCharacterMovement());
	IKScale = GetActorScale3D().Z;    
	IKTraceDistance = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

void AGCBaseCharacter::ChangeCrouchState()
{
	if(GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
	else
	{
		Crouch();
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
