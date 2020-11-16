#include "BasePlatform.h"
#include "Components/TimelineComponent.h"

ABasePlatform::ABasePlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* DefaultPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Platform root"));
	RootComponent = DefaultPlatformRoot;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	PlatformMeshComponent->SetupAttachment(DefaultPlatformRoot);
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = PlatformMeshComponent->GetRelativeLocation();
	if (IsValid(MotionCurve))
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("UpdatePlatformMove"));
		MotionTimeline.AddInterpFloat(MotionCurve, TimelineCallback);
	}
	if (PlatformBehavior == EPlatformBehavior::Loop)
	{
		FOnTimelineEvent TimelineEndCallback;
		TimelineEndCallback.BindUFunction(this, FName("StartTimerDelayMovement"));
		MotionTimeline.SetTimelineFinishedFunc(TimelineEndCallback);
		StartTimerDelayMovement();
	}
}

void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MotionTimeline.TickTimeline(DeltaTime);
}

void ABasePlatform::MovePlatform()
{
	MoveRequest();	
}

 void ABasePlatform::MoveRequest(EPlatformMoveDirection Direction)
 {	
	if (!bMovingForward && Direction != EPlatformMoveDirection::Backward)
	{
		MotionTimeline.SetPlayRate(ForwardMovingRate);
		MotionTimeline.Play();
		bMovingForward = true;
		if (OnPlatformMoved.IsBound())
		{
			OnPlatformMoved.Broadcast();
		}
	}
	else if (bMovingForward && Direction != EPlatformMoveDirection::Forward)
	{
		MotionTimeline.SetPlayRate(BackwardMovingRate);
		MotionTimeline.Reverse();
		bMovingForward = false;
		if (OnPlatformMoved.IsBound())
		{
			OnPlatformMoved.Broadcast();
		}
	}
 }

 void ABasePlatform::UpdatePlatformMove(float Value)
{
	PlatformMeshComponent->SetRelativeLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

void ABasePlatform::StartTimerDelayMovement()
{
	GetWorld()->GetTimerManager().SetTimer(MotionDelayTimer, this, &ABasePlatform::MovePlatform, MotionDelay, false);
}