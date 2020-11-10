 // Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlatform.h"
#include "Components/TimelineComponent.h"
//#include "MotionControllerComponent.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* DefaultPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Platform root"));
	RootComponent = DefaultPlatformRoot;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	PlatformMesh->SetupAttachment(DefaultPlatformRoot);
}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = PlatformMesh->GetRelativeLocation();
	if (IsValid(MotionCurve))
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("UpdatePlatformMove"));
		MotionTimeline.AddInterpFloat(MotionCurve, TimelineCallback);
	}
	if (PlatforBehavior == EPlatformBehavior::Loop)
	{
		FOnTimelineEvent TimelineEndCallback;
		TimelineEndCallback.BindUFunction(this, FName("StartTimerDelayMovement"));
		MotionTimeline.SetTimelineFinishedFunc(TimelineEndCallback);
		StartTimerDelayMovement();
	}
}

// Called every frame
void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MotionTimeline.TickTimeline(DeltaTime);
}

void ABasePlatform::MovePlatform()
{
	if (MotionTimeline.IsPlaying())
	{
		return;
	}

	bMoveingForward = !bMoveingForward;

	if (bMoveingForward)
	{
		MotionTimeline.SetPlayRate(ForwardMoveingRate);
		MotionTimeline.Play();
	}
	else
	{
		MotionTimeline.SetPlayRate(BackwardMoveingRate);
		MotionTimeline.Reverse();
	}

	if (OnPlatformMoved.IsBound())
	{
		OnPlatformMoved.Broadcast();
	}
}

void ABasePlatform::UpdatePlatformMove(float value)
{
	PlatformMesh->SetRelativeLocation((1.0f - value ) * StartLocation + value * EndLocation);
}

void ABasePlatform::StartTimerDelayMovement()
{
	GetWorld()->GetTimerManager().SetTimer(MotionDelayTimer, this, &ABasePlatform::MovePlatform, MotionDelay, false);
}

