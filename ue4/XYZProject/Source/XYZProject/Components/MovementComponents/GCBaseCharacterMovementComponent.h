// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "XYZProject/Components/LedgeDetectorComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GCBaseCharacterMovementComponent.generated.h"

struct FMantlingMovementParameters
{
	FVector InitialLocation = FVector::ZeroVector;
	FRotator InitialRotator = FRotator::ZeroRotator;

	FVector TargetLocation = FVector::ZeroVector;
	FRotator TargetRotator = FRotator::ZeroRotator;

	float Duration = 1.0f;
	float StartTime = 0.0f;

	UCurveVector* MantlingCurve;
};

UENUM(BlueprintType)
enum class ECustomMovementMode : uint8
{
	CMOVE_None = 0 UMETA(DisplayName = "None"),
	CMOVE_Mantling UMETA(DisplayName = "Mantling"),
	CMOVE_Max UMETA(Hidden)
};
/**
 * 
 */
UCLASS()
class XYZPROJECT_API UGCBaseCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void PostLoad() override;
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;
	FORCEINLINE bool IsSprinting() const { return bIsSprinting;	}
	virtual float GetMaxSpeed() const override;
	virtual bool CanAttemptJump() const override;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

	virtual void Crouch(bool bClientSimulation = false) override;//stand to crouch
	virtual void UnCrouch(bool bClientSimulation = false) override;//crouch to stand
	
	virtual void CrouchToProne(bool bClientSimulation = false);
	virtual void ProneToCrouch(bool bClientSimulation = false);
	virtual bool IsProning() const;	

	void StartSprint();
	void StopSprint();

	void StartMantle(const FMantlingMovementParameters& MantlingParameters);
	void EndMantle();
	bool IsMantling() const;

	FORCEINLINE bool IsOutOfStamina() const { return bIsOutOfStamina; }
	void SetIsOutOfStamina(bool bIsOutOfStamina_In);

	FORCEINLINE bool CanEverProne() const { return bCanProne; }
	virtual bool CanProneInCurrentState() const;

	UPROPERTY(Category="Character Movement (General Settings)", VisibleInstanceOnly, BlueprintReadOnly)
	uint8 bWantsToProne:1;

	UPROPERTY(Category="Character Movement (General Settings)", VisibleInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	uint8 bProneMaintainsBaseLocation:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NavMovement, meta = (DisplayName = "Movement Capabilities | Can Prone"))
	uint8 bCanProne:1;
	
protected:
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement: sprint", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SprintSpeed = 1100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement: sprint")
	bool bIsOutOfStamina = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement: sprint", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float OutOfStaminaSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement: prone", meta = (ClampMin = 0.0001f, UIMin = 0.0001f))
	float ProneCapsuleRadius = 40.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement: prone", meta = (ClampMin = 0.0001f, UIMin = 0.0001f))
	float ProneCapsuleHalfHeight = 40.0f;
	
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float MaxProneSpeed = 100.0f;

	UPROPERTY(Category="Character Movement: Swimming", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float SwimmingCapsuleRadius = 60.0f;
	
	UPROPERTY(Category="Character Movement: Swimming", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float SwimmingCapsuleHalfHeight = 60.0f;

	class AGCBaseCharacter* GCBaseCharacterOwner;

private:
	bool bIsSprinting;

	FMantlingMovementParameters CurrentMantlingParameters;

	FTimerHandle MantlingTimer;	
};
