#include "GCBasePawnMovementComponent.h"
#include "DrawDebugHelpers.h"

#include <string>

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
        if(bIsFalling)
        {
            VerticalVelocity += GetGravityZ() * FVector::UpVector * DeltaTime;            
        }
        if(!VerticalVelocity.IsZero())
        {
            Velocity += VerticalVelocity;    
        }        
        
        GEngine->AddOnScreenDebugMessage(-1, 5.0f,  FColor::Red,            
            FString(", Velocity: ") + Velocity.ToString() + 
            FString(", bIsFalling: ") + (bIsFalling ? FString("true") : FString("false"))
            );
    }

    const FVector Delta = Velocity * DeltaTime;

    if (bEnableGravity)
    {
        bool bWasFalling = bIsFalling;
        FHitResult HitResult;
        FVector StartPoint = UpdatedComponent->GetComponentLocation();
        float LineTraceLength = 50.0f + (bIsFalling ? - Delta.Z : 1.0f);
        FVector EndPoint = StartPoint - LineTraceLength * FVector::UpVector;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());
            
        bIsFalling = !GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, CollisionParams);
        DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 1, 0, 1);
        if(bWasFalling && !bIsFalling)
        {
             VerticalVelocity = FVector::ZeroVector;
        }
    }
    
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

void UGCBasePawnMovementComponent::JumpStart()
{
    if(!bIsFalling)
    {
        VerticalVelocity = InitialJumpVelocity * FVector::UpVector;    
    }    
}
