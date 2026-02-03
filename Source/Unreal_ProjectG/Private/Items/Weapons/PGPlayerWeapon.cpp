// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PGPlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PGGameplayTags.h"

void APGPlayerWeapon::WeaponHitTargetHandler(AActor* HitActor)
{
    check(OwningPawn.IsValid());

    // 이미 적중한 액터라면 무시
    if(OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = OwningPawn.Get();
    Data.Target = HitActor;

    // 적중한 액터에서 게임 플레이 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        OwningPawn.Get(),
        PGGameplayTags::Shared_Event_MeleeHit,
        FGameplayEventData()
    );
}

void APGPlayerWeapon::WeaponPulledFromTargetHandler(AActor* HitActor)
{
    // 나중에 히트 끝날때 처리할 게 있으면 여기에 작성
}
