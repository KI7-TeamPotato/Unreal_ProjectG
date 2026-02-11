// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Shared/SharedAbility_AOEAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "PGGameplayTags.h"

USharedAbility_AOEAttack::USharedAbility_AOEAttack()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void USharedAbility_AOEAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{


    checkf(AEOAttackMontage != nullptr, TEXT("AEOAttackMontage가 할당되지 않았습니다!"));

    // 애니메이션 몽타주 재생
    UAbilityTask_PlayMontageAndWait* AOEMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AEOAttackMontage);

    // 몽타주 완료 이벤트 바인딩
    if (AOEMontageTask)
    {
        AOEMontageTask->OnCompleted.AddUniqueDynamic(this, &USharedAbility_AOEAttack::OnAOEMontageFinished);
        AOEMontageTask->OnInterrupted.AddUniqueDynamic(this, &USharedAbility_AOEAttack::OnAOEMontageFinished);
        AOEMontageTask->OnBlendOut.AddUniqueDynamic(this, &USharedAbility_AOEAttack::OnAOEMontageFinished);
        AOEMontageTask->OnCancelled.AddUniqueDynamic(this, &USharedAbility_AOEAttack::OnAOEMontageFinished);

        AOEMontageTask->ReadyForActivation();
    }

    // 게임 플레이 이벤트 대기 태스크 생성
    UAbilityTask_WaitGameplayEvent* AOEAttackEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PGGameplayTags::Shared_Event_AOEAttackCastingComplete);

    // 이벤트 수신 핸들러 바인딩
    AOEAttackEventTask->EventReceived.AddUniqueDynamic(this, &USharedAbility_AOEAttack::OnAOECastingEnded);
    AOEAttackEventTask->ReadyForActivation();

    // 적한한 광역 공격의 중심을 찾는 로직은 TriggerEventData를 활용하여 구현할 수 있습니다.
}

void USharedAbility_AOEAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USharedAbility_AOEAttack::OnAOECastingEnded(FGameplayEventData InEventData)
{

}

void USharedAbility_AOEAttack::OnAOEMontageFinished()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
