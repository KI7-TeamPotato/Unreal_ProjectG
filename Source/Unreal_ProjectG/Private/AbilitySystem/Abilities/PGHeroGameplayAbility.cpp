// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Character/HeroCharacter.h"
#include "Character/HeroController.h"
#include "PGGameplayTags.h"

AHeroCharacter* UPGHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedHeroCharacter.IsValid())
    {
        CachedHeroCharacter = Cast<AHeroCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AHeroController* UPGHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (CachedHeroController.IsValid())
    {
        CachedHeroController = Cast<AHeroController>(CurrentActorInfo->PlayerController);
    }
    return CachedHeroCharacter.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroEquipmentComponent* UPGHeroGameplayAbility::GetHeroEquipmentComponentFromActorInfo() const
{
    // TODO : 플레이어 안에서 Getter 함수 구현
    //return GetHeroCharacterFromActorInfo()->GetPlayerEquipmentComponent();
    return nullptr;
}

FGameplayEffectSpecHandle UPGHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float SkillMultiflier)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetPGAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetPGAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        PGGameplayTags::Shared_SetByCaller_DamageMultiplier,
        SkillMultiflier
       );

    // 추가적으로 넘길 속성들이 있다면 여기에 추가

    return EffectSpecHandle;
}
