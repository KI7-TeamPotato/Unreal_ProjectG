// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PGGameplayAbility.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Components/Equipment/EquipmentComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    // 발동 정책에 따라 Passive 능력 자동 활성화
    if(AbilityActivationPolicy == EPGAbilityActivationPolicy::Passive)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}

void UPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 발동 정책에 따라 Passive 능력 자동 정리
    if (AbilityActivationPolicy == EPGAbilityActivationPolicy::Passive)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

UEquipmentComponent* UPGGameplayAbility::GetEquipmentComponent() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UEquipmentComponent>();
}

UPGAbilitySystemComponent* UPGGameplayAbility::GetPGAbilitySystemComponentFromActorInfo() const
{
    return Cast<UPGAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}

FActiveGameplayEffectHandle UPGGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    // TargetActor의 AbilitySystemComponent 가져오기
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    check(TargetASC && InSpecHandle.IsValid());

    return GetPGAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
        *InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UPGGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EPGSuccessType& OutSuccessType)
{
    FActiveGameplayEffectHandle ActivateGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

    OutSuccessType = ActivateGameplayEffectHandle.IsValid() ? EPGSuccessType::Successful : EPGSuccessType::Failed;

    return ActivateGameplayEffectHandle;
}
