// Fill out your copyright notice in the Description page of Project Settings.


#include "LedgeDetectorComponent.h"


#include "DrawDebugHelpers.h"
#include "XYZProject/XYZGameType.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "XYZProject/GCGameInstance.h"
#include "XYZProject/Characters/GCBaseCharacter.h"
#include "XYZProject/Subsystems/DebugSubsystem.h"
#include "XYZProject/Utils/GCTraceUtils.h"

bool ULedgeDetectorComponent::DetectLedge(FLedgeDescription& LedgeDescription)
{
	UCapsuleComponent* CapsuleComponent = CachedCharacterOwner->GetCapsuleComponent();

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(GetOwner());

#if ENABLE_DRAW_DEBUG
	UDebugSubsystem* DebugSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UDebugSubsystem>();
	bool bIsDebugEnabled = DebugSubsystem->IsCategoryEnabled(DebugCategoryLedgeDetection);
#else
	bool bIsDebugEnabled = false;
#endif

	float DrawTime = 2.0f;

	const float BottomZOffset = 2.0f;
	const FVector CharacterBottom = CachedCharacterOwner->GetActorLocation() - (CapsuleComponent->GetScaledCapsuleHalfHeight() - BottomZOffset) * FVector::UpVector;

	//1. Forward check
	const float ForwardCheckCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
	const float ForwardCheckCapsuleHalfHeight = (MaximumLedgeHeight - MinimumLedgeHeight) * 0.5f;

	FHitResult ForwardCheckHitResult;
	const FVector ForwardStartLocation = CharacterBottom + (MinimumLedgeHeight + ForwardCheckCapsuleHalfHeight) * FVector::UpVector;
	const FVector ForwardEndLocation = ForwardStartLocation + CachedCharacterOwner->GetActorForwardVector() * ForwardCheckDistance;

	if(!GCTraceUtils::SweepCapsuleSingleByChanel(GetWorld(), ForwardCheckHitResult, ForwardStartLocation, ForwardEndLocation, ForwardCheckCapsuleRadius, ForwardCheckCapsuleHalfHeight, FQuat::Identity, ECC_Climbing, QueryParams, FCollisionResponseParams::DefaultResponseParam, bIsDebugEnabled, DrawTime))
	{
		return false;
	}

	//2. Down check
	FHitResult DownwardCheckHitResult;
	float DownwardSphereCheckRadius = CapsuleComponent->GetScaledCapsuleRadius();

	float DownwardCheckDepthOffset = 10.0f;
	FVector DownwardStartLocation = ForwardCheckHitResult.ImpactPoint - ForwardCheckHitResult.ImpactNormal * DownwardCheckDepthOffset;
	DownwardStartLocation.Z = CharacterBottom.Z + MaximumLedgeHeight + DownwardSphereCheckRadius;
	FVector DownwardEndLocation(DownwardStartLocation.X, DownwardStartLocation.Y, CharacterBottom.Z);

	if(!GCTraceUtils::SweepSphereSingleByChanel(GetWorld(), DownwardCheckHitResult, DownwardStartLocation, DownwardEndLocation, DownwardSphereCheckRadius, FQuat::Identity,ECC_Climbing, QueryParams, FCollisionResponseParams::DefaultResponseParam, bIsDebugEnabled, DrawTime))
	{
		return false;
	}

	//3. Overlap check
	float OverlapCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
	float OverlapCapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float OverlapCapsuleOffset = 2.0f;
	FVector OverlapLocation = DownwardCheckHitResult.ImpactPoint + (OverlapCapsuleHalfHeight + OverlapCapsuleOffset) * FVector::UpVector;
	if(GCTraceUtils::OverlapCapsuleAnyByProfile(GetWorld(), OverlapLocation, OverlapCapsuleRadius, OverlapCapsuleHalfHeight, FQuat::Identity, CollisionProfilePawn, QueryParams, bIsDebugEnabled, DrawTime))
	{
		return false;
	}

	LedgeDescription.Location = OverlapLocation;
	LedgeDescription.Rotation = (ForwardCheckHitResult.ImpactNormal * FVector(-1.0f, -1.0f, 0.0f)).ToOrientationRotator();
	LedgeDescription.LedgeNormal = ForwardCheckHitResult.ImpactNormal;

	return true;
}

void ULedgeDetectorComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(GetOwner()->IsA<ACharacter>(), TEXT("ULedgeDetectorComponent::BeginPlay() only a character can use ULedgeDetectorComponent"))
	CachedCharacterOwner = StaticCast<ACharacter*>(GetOwner());
}

