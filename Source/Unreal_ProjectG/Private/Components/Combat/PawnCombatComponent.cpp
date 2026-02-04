// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbilityTypes.h"

UPawnCombatComponent::UPawnCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPawnCombatComponent::EquipWeapon(TSubclassOf<APGWeaponBase> NewWeapon)
{

}