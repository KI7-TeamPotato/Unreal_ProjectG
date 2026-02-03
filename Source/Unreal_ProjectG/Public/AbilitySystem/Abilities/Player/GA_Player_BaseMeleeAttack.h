// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGPlayerGameplayAbility.h"
#include "GA_Player_BaseMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UGA_Player_BaseMeleeAttack : public UPGPlayerGameplayAbility
{
	GENERATED_BODY()
	
public:
    UGA_Player_BaseMeleeAttack();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    // 데미지 적용 핸들러
    UFUNCTION(BlueprintCallable, Category = "Ability|Melee Attack")
    void HandleApplyDaamage(FGameplayEventData InEventData);

    UFUNCTION()
    void OnMontageFinished();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    TArray<TObjectPtr<UAnimMontage>> MeleeAttackMontages;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FGameplayTag MeleeAttackCueTag;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FGameplayTag AttackEventTag;
};
