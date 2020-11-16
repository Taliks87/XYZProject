// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.h"
#include "PlatformInvocator.generated.h"

UCLASS()
class XYZPROJECT_API APlatformInvocator : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformInvocator();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	class ABasePlatform* Platform = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	EPlatformMoveDirection MoveDirection;
};
