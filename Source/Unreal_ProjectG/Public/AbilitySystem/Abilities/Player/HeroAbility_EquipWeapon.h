// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"
#include "HeroAbility_EquipWeapon.generated.h"

class APGHeroWeapon;
/**
 *  이벤트 데이터를 통해 무기 클래스가 담긴 오브젝트를 받아 장비하는 능력
 */
UCLASS()
class UNREAL_PROJECTG_API UHeroAbility_EquipWeapon : public UPGHeroGameplayAbility
{
	GENERATED_BODY()
	
public:
    UHeroAbility_EquipWeapon();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    void LinkedAnimLayerSetup();

    void GrantWeaponAbilitiesToHero();

protected:
    TObjectPtr<APGHeroWeapon> CachedEquippedWeapon;
};
