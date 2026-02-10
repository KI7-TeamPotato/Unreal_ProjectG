// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Character/Hero/HeroCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PGGameplayTags.h"

void UHeroCombatComponent::BeginPlay()
{
    Super::BeginPlay();

       // 무기 스태틱 메시 캐싱
    AHeroCharacter* Hero = Cast<AHeroCharacter>(GetOwner());
    if (Hero)
    {
        CachedWeaponStaticMesh = Hero->GetWeaponStaticMesh();
    }
}

void UHeroCombatComponent::ActivateWeaponTrace(bool bEnableTrace, float InTraceDebugDuration)
{
    if (!CachedWeaponStaticMesh) return;

    // 트레이스를 켜서 액터를 감지하여 overrapedActor에 추가
    FVector StartLocation = CachedWeaponStaticMesh->GetSocketLocation(TEXT("WeaponTraceStart"));
    FVector EndLocation = CachedWeaponStaticMesh->GetSocketLocation(TEXT("WeaponTraceEnd"));
    ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1); //DefaultEngine.ini에서 선언된 AttackTrace 채널
    TArray<FHitResult> OutHits;

    UKismetSystemLibrary::BoxTraceMulti(
        this,
        StartLocation,
        EndLocation,
        WeaponTraceBoxExtent,
        FRotator::ZeroRotator,
        TraceChannel,
        false,
        TArray<AActor*>(),
        bEnableTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
        OutHits,
        true,
        FLinearColor::Red, FLinearColor::Green, 1.f
    );

    // 히트된 액터들 처리
    if (OutHits.Num() > 0)
    {
        for (const FHitResult& Hit : OutHits)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && HitActor != GetOwner())
            {
                OnHitTargetActor(HitActor);
            }
        }
    }
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    // 중복 데미지 처리 방지
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }
    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    // 게임 플레이 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        PGGameplayTags::Shared_Event_MeleeHit,
        Data
    );
}