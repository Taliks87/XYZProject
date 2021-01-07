// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "XYZProject/Components/MovementComponents/GCBaseCharacterMovementComponent.h"


AGCBaseCharacter::AGCBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGCBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	GCBaseCharacterMovementComponent = StaticCast<UGCBaseCharacterMovementComponent*>(GetCharacterMovement());
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
	TryChangeSprintState();
}

bool AGCBaseCharacter::CanSprint() const
{
	return true;
}

void AGCBaseCharacter::TryChangeSprintState()
{
	if(bIsSprintRequested && !GCBaseCharacterMovementComponent->IsSprinting() && CanSprint())
	{
		GCBaseCharacterMovementComponent->StartSprint();
		OnSprintStart();
	}

	if(!bIsSprintRequested && GCBaseCharacterMovementComponent->IsSprinting())
	{
		GCBaseCharacterMovementComponent->StopSprint();
		OnSprintEnd();
	}	
}
