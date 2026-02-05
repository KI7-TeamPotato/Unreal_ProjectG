// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"
#include "HeroAbility_BaseMeleeAttack.generated.h"


class UGameplayEffect;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UHeroAbility_BaseMeleeAttack : public UPGHeroGameplayAbility
{
	GENERATED_BODY()
	
public:
    UHeroAbility_BaseMeleeAttack();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    // 데미지 적용 핸들러
    UFUNCTION(BlueprintCallable, Category = "Ability|Melee Attack")
    void HandleApplyDamage(FGameplayEventData InEventData);

    UFUNCTION()
    void OnMontageFinished();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Melee Attack")
    TSubclassOf<UGameplayEffect> MeleeAttackDamageEffectClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    TArray<TObjectPtr<UAnimMontage>> MeleeAttackMontages;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FGameplayTag MeleeAttackCueTag;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FGameplayTag AttackEventTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FScalableFloat MeleeAttackSkillMultiplier;
};
