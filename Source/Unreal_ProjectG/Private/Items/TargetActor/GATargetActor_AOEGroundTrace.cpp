
#include "Items/TargetActor/GATargetActor_AOEGroundTrace.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

AGATargetActor_AOEGroundTrace::AGATargetActor_AOEGroundTrace()
{
    PrimaryActorTick.bCanEverTick = true;
    AOERadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AOERadiusSphere"));
    AOERadiusSphere->SetupAttachment(RootComponent);
    AOERadiusSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    AOERadiusSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    AOERadiusSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    AOERadiusSphere->SetGenerateOverlapEvents(true);
}

void AGATargetActor_AOEGroundTrace::StartTargeting(UGameplayAbility* InAbility)
{
    Super::StartTargeting(InAbility);

    // 오버랩 이벤트 바인딩
    AOERadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &AGATargetActor_AOEGroundTrace::OnSphereOverlapBegin);
    AOERadiusSphere->OnComponentEndOverlap.AddDynamic(this, &AGATargetActor_AOEGroundTrace::OnSphereOverlapEnd);

    AOERadiusSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    if (APlayerController* PC = Cast<APlayerController>(PrimaryPC))
    {
        // 터치 이벤트 활성화
        PC->bEnableTouchEvents = true;
    }
}

void AGATargetActor_AOEGroundTrace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    ClearAllHighlightedActors();
    Super::EndPlay(EndPlayReason);
}

void AGATargetActor_AOEGroundTrace::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!PrimaryPC)
    {
        return;
    }

    FVector2D TouchLocation;
    bool bIsCurrentlyTouching = false;

    if(APlayerController* PC = Cast<APlayerController>(PrimaryPC))
    {
        PC->GetInputTouchState(ETouchIndex::Touch1, TouchLocation.X, TouchLocation.Y, bIsCurrentlyTouching);
    }

    if (bIsCurrentlyTouching && !bIsTouching)
    {
        OnTouchPressed();
    }
    else if (!bIsCurrentlyTouching && bIsTouching)
    {
        OnTouchReleased();
    }

    if (bIsTouching)
    {
        FVector WorldLocation, WorldDirection;
        if (PrimaryPC->DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, WorldLocation, WorldDirection))
        {
            FHitResult HitResult;
            FVector TraceEnd = WorldLocation + (WorldDirection * 10000.0f);

            if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility))
            {
                LastTouchLocation = HitResult.Location;

                // 디칼 위치 업데이트
                if (SpawnedDecalComponent.IsValid())
                {
                    SpawnedDecalComponent->SetWorldLocation(HitResult.Location);
                }
            }
        }
    }

    bIsTouching = bIsCurrentlyTouching;
}

void AGATargetActor_AOEGroundTrace::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AGATargetActor_AOEGroundTrace::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AGATargetActor_AOEGroundTrace::OnTouchPressed()
{
    bIsTouching = true;

    SpawnedDecalComponent = UGameplayStatics::SpawnDecalAttached(
        AOETraceDecalMaterial,
        FVector(10, AOETraceRadius, AOETraceRadius),
        GetRootComponent(),
        NAME_None,
        FVector::ZeroVector,
        FRotator(-90.f, 0.f, 0.0f),
        EAttachLocation::KeepRelativeOffset
    );
}

void AGATargetActor_AOEGroundTrace::OnTouchReleased()
{
    bIsTouching = false;
}

void AGATargetActor_AOEGroundTrace::OnHighlightActorInAOE(AActor* InActor)
{

}

void AGATargetActor_AOEGroundTrace::OnUnhighlightActorOutAOE(AActor* InActor)
{

}

void AGATargetActor_AOEGroundTrace::ClearAllHighlightedActors()
{
}

//FHitResult AGATargetActor_AOEGroundTrace::PerformTrace(AActor* InSourceActor)
//{
//    TargetDataReadyDelegate
//    return FHitResult();
//}
