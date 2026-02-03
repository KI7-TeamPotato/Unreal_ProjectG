// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PGPlayerGameplayAbility.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "PGGameplayTags.h"

#include "GameFramework//Character.h"

ACharacter* UPGPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
    if (!CachedPlayerCharacter.IsValid())
    {
        // TODO : 우리의 플레이어 캐릭터 타입으로 변경
        CachedPlayerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

APlayerController* UPGPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    if (CachedPlayerController.IsValid())
    {
        // TODO : 우리의 플레이어 컨트로러 타입으로 변경
        CachedPlayerController = Cast<APlayerController>(CurrentActorInfo->PlayerController);
    }
    return CachedPlayerCharacter.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerEquipmentComponent* UPGPlayerGameplayAbility::GetPlayerEquipmentComponentFromActorInfo() const
{
    // TODO : 플레이어 안에서 Getter 함수 구현
    //return GetPlayerCharacterFromActorInfo()->GetPlayerEquipmentComponent();
    return nullptr;
}

FGameplayEffectSpecHandle UPGPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float SkillMultiflier)
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
