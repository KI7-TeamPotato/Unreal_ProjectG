// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGGameplayAbility.h"
#include "SharedAbility_SpawnWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API USharedAbility_SpawnWeapon : public UPGGameplayAbility
{
	GENERATED_BODY()
	

public:
    USharedAbility_SpawnWeapon();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|EquipWeapon")
    FName EquipWeaponAttachmentSocketName = FName("WeaponSocket");
};
