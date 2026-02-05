// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Objects/EquipWeaponEventDataObject.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PGGameplayTags.h"

UPawnCombatComponent::UPawnCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPawnCombatComponent::TryEquippedWeaponFromEvent(TSubclassOf<APGWeaponBase> NewWeapon)
{
    // 클래스를 오브젝트에 담아서 SendGameplayEventToActor로 보내는 방식
    UEquipWeaponEventDataObject* EquipWeaponDataObject = NewObject<UEquipWeaponEventDataObject>();
    EquipWeaponDataObject->InitializeEquipWeaponEventData(NewWeapon);

    FGameplayEventData EventData;
    EventData.OptionalObject = EquipWeaponDataObject;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), PGGameplayTags::Player_Event_WeaponEquipped, EventData);
}

void UPawnCombatComponent::SetWeaponEquipped(APGWeaponBase* InEquippedWeapon, bool bIsEquipped)
{
    CurrentEquippedWeapon = InEquippedWeapon;
    bWeaponEquipped = bIsEquipped;
}
