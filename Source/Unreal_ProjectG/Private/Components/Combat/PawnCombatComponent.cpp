// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PGGameplayTags.h"

UPawnCombatComponent::UPawnCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPawnCombatComponent::SetbWeaponEquipped(bool InBoolean)
{
    bWeaponEquipped = InBoolean;
}

void UPawnCombatComponent::AssignSkillAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InHandle)
{
    GrantedSkillAbilitySpecHandles = InHandle;
}

void UPawnCombatComponent::AssignBaseAttackAbilitySpecHandle(const FGameplayAbilitySpecHandle& InHandle)
{
    GrantedBaseAttackAbilitySpecHandle = InHandle;
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    return;
}
