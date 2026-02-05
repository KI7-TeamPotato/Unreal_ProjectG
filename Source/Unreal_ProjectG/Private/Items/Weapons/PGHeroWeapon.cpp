// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PGHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PGGameplayTags.h"

void APGHeroWeapon::WeaponHitTargetHandler(AActor* HitActor)
{
    check(Owner);

    // 이미 적중한 액터라면 무시
    if(OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = Owner;
    Data.Target = HitActor;

    // 적중한 액터에서 게임 플레이 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        Owner,
        PGGameplayTags::Shared_Event_MeleeHit,
        Data
    );
}

void APGHeroWeapon::WeaponPulledFromTargetHandler(AActor* HitActor)
{
    // 나중에 히트 끝날때 처리할 게 있으면 여기에 작성
}
