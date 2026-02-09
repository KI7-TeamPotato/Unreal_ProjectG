// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/DataAsset_HeroStartupData.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"

void UDataAsset_HeroStartupData::GiveToAbilitySystemComponent(UPGAbilitySystemComponent* InASCToGive, int32 InLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, InLevel);
    // 태그와 어빌리티 매핑이 필요해지면 사용
    for (const FPGHeroAbilitySet& AbilitySet : HeroAbilitySets)
    {
        if (!AbilitySet.IsValid())
        {
            continue;
        }
        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = InLevel;
        AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

        InASCToGive->GiveAbility(AbilitySpec);
    }
}
