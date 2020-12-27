#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCodeBasePawn.generated.h"

UCLASS()
class XYZPROJECT_API AGameCodeBasePawn : public APawn
{
	GENERATED_BODY()

public:
	AGameCodeBasePawn();

	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComponent;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetInputForward() const { return InputForward; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetInputRight() const { return InputRight; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base pawn")
	float CollisionSphereRadius = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base pawn")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base pawn")
	class UCameraComponent* CameraComponent;

#if	WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base pawn")
	class UArrowComponent* ArrowComponent;
#endif
	
private:
	UFUNCTION()
	void OnBlendComplete();

	float InputForward = 0.0f;
	float InputRight = 0.0f;
	
	AActor* CurrentViewActor;
};
