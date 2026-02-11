// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGGameplayAbility.h"
#include "SharedAbility_AOEAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API USharedAbility_AOEAttack : public UPGGameplayAbility
{
	GENERATED_BODY()
	
public:
    USharedAbility_AOEAttack();
    
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    UFUNCTION()
    void OnAOECastingEnded(FGameplayEventData InEventData);

    UFUNCTION()
    void OnAOEMontageFinished();
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|AOE Attack")
    TSubclassOf<UGameplayEffect> AOEAttackDamageEffectClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|AOE Attack")
    TObjectPtr<UAnimMontage> AEOAttackMontage;

    // 데미지가 들어갈 때 호출될 게임 플레이 큐
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|AOE Attack")
    FGameplayTag AEOImpactCueTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|AOE Attack")
    int32 MaxHitTargets = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|AOE Attack")
    float AOEAttackRadius = 300.f;
};
