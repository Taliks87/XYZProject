#include "PlatformInvocator.h"
#include "Components/BoxComponent.h"

APlatformInvocator::APlatformInvocator()
{ 	
	PrimaryActorTick.bCanEverTick = false;
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColision"));
	BoxCollisionComponent->SetBoxExtent(FVector(100.0f,100.0f,100.0f), true);
	BoxCollisionComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxCollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlatformInvocator::BeginPlay()
{
	Super::BeginPlay();	
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformInvocator::OnBeginOverlap);			
}

void APlatformInvocator::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Platform)
	{
		Platform->MoveRequest(MoveDirection);
	}
}

