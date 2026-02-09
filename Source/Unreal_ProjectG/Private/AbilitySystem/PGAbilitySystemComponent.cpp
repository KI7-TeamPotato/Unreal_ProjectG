// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"

void UPGAbilitySystemComponent::GrantHeroWeaponBasicAttackAbility(FPGHeroAbilitySet InBasicAttackAbility, int32 ApplyLevel, FGameplayAbilitySpecHandle& OutBasicAttackAbilitySpecHandle)
{
    if (!InBasicAttackAbility.IsValid()) return;

    FGameplayAbilitySpec AbilitySpec(InBasicAttackAbility.AbilityToGrant);
    
    AbilitySpec.SourceObject = GetAvatarActor();
    AbilitySpec.Level = ApplyLevel;
    AbilitySpec.GetDynamicSpecSourceTags().AddTag(InBasicAttackAbility.InputTag);

    OutBasicAttackAbilitySpecHandle = GiveAbility(AbilitySpec);
}

void UPGAbilitySystemComponent::GrantHeroWeaponSkillAbilities(const TArray<FPGHeroAbilitySet>& InWeaponSkillAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutWeaponAbilitySpecHandles)
{
    if (InWeaponSkillAbilities.IsEmpty()) return;

    for (const FPGHeroAbilitySet& AbilitySet : InWeaponSkillAbilities)
    {
        if(!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

        // 부여한 어빌리티 삭제를 위해 핸들을 저장
        OutWeaponAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
    }
}
