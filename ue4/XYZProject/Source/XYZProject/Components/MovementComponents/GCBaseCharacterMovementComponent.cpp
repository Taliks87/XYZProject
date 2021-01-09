// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacterMovementComponent.h"

float UGCBaseCharacterMovementComponent::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();
	if(bIsSprinting)
	{
		Result = SprintSpeed;
	} else if(bIsOutOfStamina)
	{
		Result = OutOfStaminaSpeed;
	}
	return Result;
}

bool UGCBaseCharacterMovementComponent::CanAttemptJump() const
{
	return Super::CanAttemptJump() && !bIsOutOfStamina;
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
