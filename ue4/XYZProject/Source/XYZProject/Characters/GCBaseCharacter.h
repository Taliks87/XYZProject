#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GCBaseCharacter.generated.h"

class UGCBaseCharacterMovementComponent;

UCLASS(Abstract, NotBlueprintable)
class XYZPROJECT_API AGCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGCBaseCharacter(const FObjectInitializer& ObjectInitializer);
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void Turn(float Value) {};
	virtual void LookUp(float Value) {};
	virtual void TurnAtRate(float Value) {};
	virtual void LookUpAtRate(float Value) {};

	virtual void ChangeCrouchState();
	virtual void ChangeProneState();
	virtual void StartSprint();
	virtual void StopSprint();
    virtual void Jump() override;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	FORCEINLINE UGCBaseCharacterMovementComponent* GetBaseCharacterMovementComponent() const { return GCBaseCharacterMovementComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetIKRightFootOffset() const { return IKRightFootOffset; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetIKLeftFootOffset() const {	return IKLeftFootOffset; }

	virtual void Crouch(bool bClientSimulation = false) override;

	virtual void OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust) override;
	virtual void OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust) override;
	virtual void OnEndProne(float HeightAdjust, float ScaledHeightAdjust);
	virtual void OnStartProne(float HeightAdjust, float ScaledHeightAdjust);	

	UFUNCTION(BlueprintCallable, Category=Character, meta=(HidePin="bClientSimulation"))
	virtual void Prone(bool bClientSimulation = false);

	UFUNCTION(BlueprintCallable, Category=Character, meta=(HidePin="bClientSimulation"))
	virtual void UnProne(bool bClientSimulation = false);

	UFUNCTION(BlueprintCallable, Category=Character)
	virtual bool CanProne() const;

	UPROPERTY(BlueprintReadOnly, Category=Character)	
	bool bIsProned;

	virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;	

protected:

	UFUNCTION(BlueprintNativeEvent, Category = " Character | Movement")
	void OnSprintStart();
	virtual void OnSprintStart_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = " Character | Movement")
	void OnSprintEnd();
	virtual void OnSprintEnd_Implementation() {};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Controls")
	float BaseTurnRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Controls")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement")
	float SprintSpeed = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float MaxStamina = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement", meta = (ClampMin = 0.0001f, UIMin = 0.0001f))
	float StaminaRestoreVelocity = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement", meta = (ClampMin = 0.0001f, UIMin = 0.0001f))
	float SprintStaminaConsumptionVelocity = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | IK Settings")
	FName RightFootSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | IK Settings")
	FName LeftFootSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | IK settings", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float IKTraceExtendDistance = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | IK settings", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float IKInterpSpeed = 20.0f;

	virtual bool CanSprint() const;

	virtual bool CanJumpInternal_Implementation() const override;

	UGCBaseCharacterMovementComponent* GCBaseCharacterMovementComponent;

private:
	float GetIKOffsetForASocket(const FName& SocketName) const;
	void RefreshStamina(float DeltaTime);
	void RecalculateMashOffset(float HeightAdjust, float ScaledHeightAdjust);
		
	bool bIsSprintRequested;
	
	float IKRightFootOffset = 0.0f;
	float IKLeftFootOffset = 0.0f;
	float IKTraceDistance = 0.0f;
	float IKScale = 0.0f;

	float CurrentStamina = 0.0f;
};
