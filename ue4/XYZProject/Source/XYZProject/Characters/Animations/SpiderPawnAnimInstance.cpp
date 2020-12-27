#include "SpiderPawnAnimInstance.h"

#include "XYZProject/Characters/SpiderPawn.h"

void USpiderPawnAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    checkf(TryGetPawnOwner()->IsA<ASpiderPawn>(), TEXT("USpiderPawnAnimInstance::NativeBeginPlay() USpiderPawnAnimInstance can be used with sider pawn only"));
    CachedSpiderPawnOwner = StaticCast<ASpiderPawn*>(TryGetPawnOwner());
}

void USpiderPawnAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
   Super::NativeUpdateAnimation(DeltaSecond);

    if(!CachedSpiderPawnOwner.IsValid())
    {
        return;
    }

    RightFrontFootEffectorLocation = FVector(CachedSpiderPawnOwner->GetIKRightFrontFootOffset(), 0.0f, 0.0f);
    RightRearFootEffectorLocation = FVector(CachedSpiderPawnOwner->GetIKRightRearFootOffset(), 0.0f, 0.0f);
    LeftFrontFootEffectorLocation = FVector(CachedSpiderPawnOwner->GetIKLeftFrontFootOffset(), 0.0f, 0.0f);
    LeftRearFootEffectorLocation = FVector(CachedSpiderPawnOwner->GetIKLeftRearFootOffset(), 0.0f, 0.0f);
}
