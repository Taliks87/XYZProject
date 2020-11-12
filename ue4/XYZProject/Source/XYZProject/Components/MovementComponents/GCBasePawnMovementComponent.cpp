// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBasePawnMovementComponent.h"

void UGCBasePawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    if(ShouldSkipUpdate(DeltaTime))
    {
        return;    
    }
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const FVector PendingInput = GetPendingInputVector().GetClampedToMaxSize(1.0f);
    Velocity = PendingInput * MaxSpeed;
    ConsumeInputVector();

    if (bEnableGravity)
    {
        VerticalVelocity += GetGravityZ() * FVector::UpVector;
        Velocity += VerticalVelocity;
    }

    const FVector Delta = Velocity * DeltaTime;
    if(!Delta.IsNearlyZero(1e-6f))
    {
        FQuat Rotation = UpdatedComponent->GetComponentQuat();
        MoveUpdatedComponent(Delta, Rotation, true);
        FHitResult Hit(1.f);
        SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

        if (Hit.IsValidBlockingHit())
        {
            HandleImpact(Hit, DeltaTime, Delta);
            // Try to slide the remaining distance along the surface.
            SlideAlongSurface(Delta, 1.f-Hit.Time, Hit.Normal, Hit, true);
        }
    }

    UpdateComponentVelocity();
}
