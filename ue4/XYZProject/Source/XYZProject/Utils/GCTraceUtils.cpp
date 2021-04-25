#include "GCTraceUtils.h"

#include "DrawDebugHelpers.h"

bool GCTraceUtils::SweepCapsuleSingleByChanel(const UWorld* World, FHitResult& OutHit, const FVector& Start,
                                              const FVector& End, float CapsuleRadius, float CapsuleHalfHeight, const FQuat& Rot,
                                              ECollisionChannel TraceChannel, const FCollisionQueryParams& Params,
                                              const FCollisionResponseParams& ResponseParam, bool bDrawDebug, float DrawTime, FColor TraceColor, FColor HitColor)
{
    bool bResult = false;
    const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
    bResult = World->SweepSingleByChannel(OutHit, Start, End, Rot, TraceChannel, CollisionShape, Params, ResponseParam);

#if ENABLE_DRAW_DEBUG
    if(bDrawDebug)
    {
        DrawDebugCapsule(World, Start, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, TraceColor, false, DrawTime);
        DrawDebugCapsule(World, End, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, TraceColor, false, DrawTime);
        DrawDebugLine(World, Start, End, TraceColor, false, DrawTime);

        if(bResult)
        {
            DrawDebugCapsule(World, OutHit.Location, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, HitColor, false, DrawTime);
            DrawDebugPoint(World, OutHit.ImpactPoint, 10.0f, FColor::Red, false, DrawTime);    
        }
    }
#endif
    
    return bResult;
}

bool GCTraceUtils::SweepSphereSingleByChanel(const UWorld* World, FHitResult& OutHit, const FVector& Start,
    const FVector& End, float Radius, const FQuat& Rot, ECollisionChannel TraceChannel,
    const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam, bool bDrawDebug, float DrawTime,
    FColor TraceColor, FColor HitColor)
{
    bool bResult = false;
    const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);
    bResult = World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, TraceChannel, CollisionShape, Params, ResponseParam);

#if ENABLE_DRAW_DEBUG
    if(bDrawDebug)
    {
        FVector DebugCenter = (Start + End) * 0.5f;
        FVector TraceVector = End - Start;
        float DebugDrawCapsuleHalfHeight = TraceVector.Size() * 0.5f;

        FQuat DebugCapsuleRotation = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();
        
        DrawDebugCapsule(World, DebugCenter, DebugDrawCapsuleHalfHeight, Radius, DebugCapsuleRotation, TraceColor, false, DrawTime);

        
        DrawDebugSphere(World, OutHit.Location, Radius, 16, HitColor, false, DrawTime);
        DrawDebugPoint(World, OutHit.ImpactPoint, 10.0f, HitColor, false, DrawTime);
    }
#endif
    
    return bResult;
}

bool GCTraceUtils::OverlapCapsuleAnyByProfile(const UWorld* World, const FVector& Pos, float CapsuleRadius,
    float CapsuleHalfHeight, FQuat Rotation, FName ProfileName, const FCollisionQueryParams QueryParams,
    bool bDrawDebug, float DrawTime, FColor HitColor)
{
    bool bResult = false;

    const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
    bResult = World->OverlapAnyTestByProfile(Pos, Rotation, ProfileName, CollisionShape, QueryParams);
    
#if ENABLE_DRAW_DEBUG
    if (bDrawDebug && bResult)
    {
        DrawDebugCapsule(World, Pos, CapsuleHalfHeight, CapsuleRadius, Rotation, HitColor, false, DrawTime);
    }
#endif
    
    return bResult;
}
