// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/GA_Die.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Character/Hero/HeroCharacter.h"


UGA_Die::UGA_Die()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Die::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    AHeroCharacter* Hero = Cast<AHeroCharacter>(ActorInfo->AvatarActor.Get());
    if (Hero)
    {
        Hero->OnDie();

        UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, RespawnTime);
        if (DelayTask)
        {
            DelayTask->OnFinish.AddDynamic(this, &UGA_Die::RespawnHero);
            DelayTask->ReadyForActivation();
        }
    }
}

void UGA_Die::RespawnHero()
{
    AHeroCharacter* Hero = Cast<AHeroCharacter>(CurrentActorInfo->AvatarActor.Get());
    if (Hero)
    {
        Hero->SpawnHero();
    }
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
