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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlatformMoved);

UCLASS()
class XYZPROJECT_API ABasePlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MovePlatform();

private:
	UFUNCTION()
	void UpdatePlatformMove(float value);

	UFUNCTION()
	void StartTimerDelayMovement();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Platform settings", meta = (MakeEditWidget))
	FVector EndLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient);
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	EPlatformBehavior PlatforBehavior = EPlatformBehavior::OnDemand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	UCurveFloat* MotionCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0001f, ClampMin = 0.0001f))
	float ForwardMoveingRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0001f, ClampMin = 0.0001f))
	float BackwardMoveingRate = 1.0f;

	UPROPERTY(BlueprintAssignable, Category = "Platform settings")
	FOnPlatformMoved OnPlatformMoved;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float MotionDelay = 1.0f;

private:
	bool bMoveingForward = false;
	FTimerHandle MotionDelayTimer;
	FTimeline MotionTimeline;
};
