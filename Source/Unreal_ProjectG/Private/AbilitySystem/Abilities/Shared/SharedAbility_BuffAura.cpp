// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Shared/SharedAbility_BuffAura.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"

void USharedAbility_BuffAura::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    BuffAuraSphere = NewObject<USphereComponent>(GetAvatarActorFromActorInfo());
    BuffAuraSphere->SetupAttachment(GetAvatarActorFromActorInfo()->GetRootComponent());
    BuffAuraSphere->SetSphereRadius(BuffAuraRadius);
    BuffAuraSphere->RegisterComponent(); // 컴포넌트 등록

    //// 오버랩 이벤트 바인딩
    BuffAuraSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &USharedAbility_BuffAura::OnAuraBeginOverlap);
    BuffAuraSphere->OnComponentEndOverlap.AddUniqueDynamic(this, &USharedAbility_BuffAura::OnAuraEndOverlap);
}

void USharedAbility_BuffAura::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 버프 오라가 적용된 액터들에게 버프 제거 후 정리
    if (ActiveBuffsOnTargets.Num() > 0)
    {
        for(const auto& Elem : ActiveBuffsOnTargets)
        {
            AActor* TargetActor = Elem.Key;
            FActiveGameplayEffectHandle EffectHandle = Elem.Value;
            NativeRemoveActiveGameplayEffectFromTarget(TargetActor, EffectHandle);
        }
        ActiveBuffsOnTargets.Empty();
    }

    // 버프 오라 컴포넌트 제거
    if (BuffAuraSphere)
    {
        BuffAuraSphere->DestroyComponent();
        BuffAuraSphere = nullptr;
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USharedAbility_BuffAura::OnAuraBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 전방 검사
    if (ActiveBuffsOnTargets.Contains(OtherActor)) return;

    ApplyBuffAuraEffectToTarget(OtherActor);
}

void USharedAbility_BuffAura::OnAuraEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ActiveBuffsOnTargets.Contains(OtherActor))
    {
<<<<<<< Updated upstream
        FActiveGameplayEffectHandle& EffectHandle = ActiveBuffsOnTargets[OtherActor];
        NativeRemoveActiveGameplayEffectFromTarget(OtherActor, EffectHandle);
        ActiveBuffsOnTargets.Remove(OtherActor);
=======
        if (TArray<FActiveGameplayEffectHandle>* Handles = ActiveBuffsOnTargets.Find(Key))
        {
            for(const FActiveGameplayEffectHandle& EffectHandle : *Handles)
            {
                NativeRemoveActiveGameplayEffectFromTarget(OtherActor, EffectHandle);
            }
            ActiveBuffsOnTargets.Remove(Key);
        }
    }
}

void USharedAbility_BuffAura::BuildCachedBuffEffectSpecs()
{
    CachedNumericBuffSpecs.Empty();
    CachedStatusBuffSpecs.Empty();

    //수치형 버프
    for (const FNumericBuffEffectConfig& Buff : BuffAuraConfig.NumericBuffs)
    {
        if (Buff.EffectClass)
        {
            FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Buff.EffectClass.Get(), GetAbilityLevel());
            
            // 버프 효과의 magnitude를 설정
            if (SpecHandle.IsValid())
            {
                const float Multiplier = Buff.SkillMultiplier.GetValueAtLevel(GetAbilityLevel());
                const float BaseAmount = Buff.BaseBuffAmount.GetValueAtLevel(GetAbilityLevel());

                SpecHandle.Data->SetSetByCallerMagnitude(PGGameplayTags::Shared_SetByCaller_SkillMultiplier, Multiplier);
                SpecHandle.Data->SetSetByCallerMagnitude(PGGameplayTags::Shared_SetByCaller_BaseBuffAmount, BaseAmount);
            }
            CachedNumericBuffSpecs.Add(SpecHandle);
        }
    }

    // 상태형 버프
    for (const TSubclassOf<UGameplayEffect>& EffectClass : BuffAuraConfig.StatusEffectClasses)
    {
        if (EffectClass)
        {
            FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(EffectClass.Get(), GetAbilityLevel());
            CachedStatusBuffSpecs.Add(SpecHandle);
        }
>>>>>>> Stashed changes
    }
}

void USharedAbility_BuffAura::ApplyBuffAuraEffectToTarget(AActor* TargetActor)
{
    if (TargetActor && BuffAuraEffectClass)
    {
        FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(BuffAuraEffectClass, GetAbilityLevel());
        FActiveGameplayEffectHandle ActiveEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, SpecHandle);
        if (ActiveEffectHandle.IsValid())
        {
            ActiveBuffsOnTargets.Add(TargetActor, ActiveEffectHandle);
        }
    }
}


