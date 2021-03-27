#pragma once

#include "CoreMinimal.h"
#include "GCBaseCharacter.h"
#include "Components/TimelineComponent.h"

#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class XYZPROJECT_API APlayerCharacter : public AGCBaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;
	virtual void TurnAtRate(float Value) override;
	virtual void LookUpAtRate(float Value) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void SwimForward(float Value) override;
	virtual void SwimRight(float Value) override;
	virtual void SwimUp(float Value) override;
	
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnJumped_Implementation() override;
	
protected:
	virtual void OnSprintStart_Implementation() override;
	virtual void OnSprintEnd_Implementation() override;
	
private:
	UFUNCTION()
	void UpdateSpringArmLength(float Value);
	
protected:		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Sprint Settings", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SprintSpringArmLength = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Sprint Settings")
	UCurveFloat* SprintSpringArmCurve = nullptr;	

private:	
	float DefaultSpringArmLength;	
	FTimeline SprintSpringArmTimeline;
};
