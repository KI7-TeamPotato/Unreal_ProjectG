// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Die.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UGA_Die : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

    UGA_Die();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    // 어빌리티를 발동시키는 입력이 끝났을 때 실행될 함수
    virtual void InputReleased(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float RespawnTime = 10.0f;

};
