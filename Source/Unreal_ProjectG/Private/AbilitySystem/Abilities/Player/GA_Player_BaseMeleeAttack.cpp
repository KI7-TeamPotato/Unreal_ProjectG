// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/GA_Player_BaseMeleeAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "PGGameplayTags.h"
#include "GameplayCueFunctionLibrary.h"

UGA_Player_BaseMeleeAttack::UGA_Player_BaseMeleeAttack()
{
    // 기본 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Player_BaseMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    // 애니메이션 몽타주 재생
    UAnimMontage* SelectedMontage = MeleeAttackMontages[FMath::RandRange(0, MeleeAttackMontages.Num() - 1)];
    UAbilityTask_PlayMontageAndWait* MeleeMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, SelectedMontage);
    
    // 몽타주 완료 이벤트 바인딩
    if (MeleeMontageTask)
    {
        MeleeMontageTask->OnCompleted.AddUniqueDynamic(this, &UGA_Player_BaseMeleeAttack::OnMontageFinished);
        MeleeMontageTask->OnInterrupted.AddUniqueDynamic(this, &UGA_Player_BaseMeleeAttack::OnMontageFinished);
        MeleeMontageTask->OnBlendOut.AddUniqueDynamic(this, &UGA_Player_BaseMeleeAttack::OnMontageFinished);
        MeleeMontageTask->OnCancelled.AddUniqueDynamic(this, &UGA_Player_BaseMeleeAttack::OnMontageFinished);

        MeleeMontageTask->ReadyForActivation();
    }


    // 게임플레이 이벤트 대기 태스크 생성
    UAbilityTask_WaitGameplayEvent* MeleeHitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, AttackEventTag);

    // 이벤트 수신 핸들러 바인딩
    MeleeHitEventTask->EventReceived.AddUniqueDynamic(this, &UGA_Player_BaseMeleeAttack::HandleApplyDaamage);
    MeleeHitEventTask->ReadyForActivation();
}

void UGA_Player_BaseMeleeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Player_BaseMeleeAttack::HandleApplyDaamage(FGameplayEventData InEventData)
{
    // 게임플레이 큐 실행
    UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(GetAvatarActorFromActorInfo(), MeleeAttackCueTag, FGameplayCueParameters());

    AActor* TargetActor = const_cast<AActor*>(InEventData.Target.Get());
    
    // TODO : 스킬의 데미지 Multiflier를 변수화
    FGameplayEffectSpecHandle EffectSpecHandle = MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect>(), 1.0f);
    
    NativeApplyEffectSpecHandleToTarget(TargetActor, EffectSpecHandle);
}

void UGA_Player_BaseMeleeAttack::OnMontageFinished()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
