
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

    AOERadiusSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AOERadiusSphere->SetGenerateOverlapEvents(true);
}

void AGATargetActor_AOEGroundTrace::StartTargeting(UGameplayAbility* InAbility)
{
    Super::StartTargeting(InAbility);

    // 오버랩 이벤트 바인딩
    AOERadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &AGATargetActor_AOEGroundTrace::OnSphereOverlapBegin);
    AOERadiusSphere->OnComponentEndOverlap.AddDynamic(this, &AGATargetActor_AOEGroundTrace::OnSphereOverlapEnd);

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

    FVector2D TouchLocation = FVector2D::ZeroVector;
    bool bIsCurrentlyTouching = false;

    if(APlayerController* PC = Cast<APlayerController>(PrimaryPC))
    {
        PC->GetInputTouchState(ETouchIndex::Touch1, TouchLocation.X, TouchLocation.Y, bIsCurrentlyTouching);
    }

    // 터치 시작 및 종료 감지
    if (bIsCurrentlyTouching && !bIsTouching)
    {
        OnTouchPressed();
    }
    else if (!bIsCurrentlyTouching && bIsTouching)
    {
        OnTouchReleased();
    }

    bIsTouching = bIsCurrentlyTouching;

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

                SetActorLocation(LastTouchLocation);
            }
        }
    }

    DrawDebugSphere(GetWorld(), LastTouchLocation, AOERadiusSphere->GetScaledSphereRadius(), 12, FColor::Red, false, -1, 0, 2);

}

void AGATargetActor_AOEGroundTrace::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 오버랩 팀 확인 및 리턴 추가
    if (!OtherActor)
        return;
    if (OverlappedActors.Contains(OtherActor))
        return;

    // 플레이어 자신의 캐릭터는 무시
    if (PrimaryPC && PrimaryPC->GetPawn() == OtherActor)
        return;

    // 오버랩된 액터 추가
    OverlappedActors.AddUnique(OtherActor);
    OnHighlightActorInAOE(OtherActor);
}

void AGATargetActor_AOEGroundTrace::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor)
        return;
    if(!OverlappedActors.Contains(OtherActor))
        return;

    // 오버랩된 액터 제거
    OverlappedActors.Remove(OtherActor);
    OnUnhighlightActorOutAOE(OtherActor);
}

void AGATargetActor_AOEGroundTrace::OnTouchPressed()
{
    // 터치 시작 시에 데칼 컴포넌트 생성
    bIsTouching = true;

    AOEDecalComponent = UGameplayStatics::SpawnDecalAttached(
        AOETraceDecalMaterial,
        FVector(10, AOETraceRadius, AOETraceRadius),
        GetRootComponent(),
        NAME_None,
        FVector::ZeroVector,
        FRotator(-90.f, 0.f, 0.0f),
        EAttachLocation::KeepRelativeOffset
    );
    
    // 스피어 컴포넌트의 반지름을 설정
    AOERadiusSphere->SetSphereRadius(AOETraceRadius);
    AOERadiusSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGATargetActor_AOEGroundTrace::OnTouchReleased()
{
    bIsTouching = false;
    if (AOEDecalComponent.IsValid())
    {
        AOEDecalComponent->DestroyComponent();
        AOEDecalComponent = nullptr;
    }
    AOERadiusSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FGameplayAbilityTargetDataHandle TargetData;

    // HitLocation만 넘기기
}

void AGATargetActor_AOEGroundTrace::OnHighlightActorInAOE(AActor* InActor)
{
    UE_LOG(LogTemp, Log, TEXT("Highlight Actor In AOE: %s"), *InActor->GetName());
}

void AGATargetActor_AOEGroundTrace::OnUnhighlightActorOutAOE(AActor* InActor)
{
    UE_LOG(LogTemp, Log, TEXT("Unhighlight Actor Out AOE: %s"), *InActor->GetName());
}

void AGATargetActor_AOEGroundTrace::ClearAllHighlightedActors()
{
    for(AActor* Actor : OverlappedActors)
    {
        OnUnhighlightActorOutAOE(Actor);
    }
    OverlappedActors.Empty();
}
