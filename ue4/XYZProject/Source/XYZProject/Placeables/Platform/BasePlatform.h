// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "BasePlatform.generated.h"

UENUM()
enum class EPlatformBehavior : uint8
{
	OnDemand = 0,
	Loop
};

UENUM()
enum class EPlatformMoveDirection : uint8
{
	Anywhere = 0,
	Forward,
	Backward
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlatformMoved);

UCLASS()
class XYZPROJECT_API ABasePlatform : public AActor
{
	GENERATED_BODY()

public:
	ABasePlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MovePlatform();

	void MoveRequest(EPlatformMoveDirection Direction = EPlatformMoveDirection::Anywhere);

private:
	UFUNCTION()
	void UpdatePlatformMove(float Value);

	UFUNCTION()
	void StartTimerDelayMovement();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	UStaticMeshComponent* PlatformMeshComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Platform settings", meta = (MakeEditWidget))
	FVector EndLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient);
	FVector StartLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	EPlatformBehavior PlatformBehavior = EPlatformBehavior::OnDemand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	UCurveFloat* MotionCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0001f, ClampMin = 0.0001f))
	float ForwardMovingRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0001f, ClampMin = 0.0001f))
	float BackwardMovingRate = 1.0f;

	UPROPERTY(BlueprintAssignable, Category = "Platform settings")
	FOnPlatformMoved OnPlatformMoved;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float MotionDelay = 1.0f;

private:
	bool bMovingForward = false;
	FTimerHandle MotionDelayTimer;
	FTimeline MotionTimeline;
};
