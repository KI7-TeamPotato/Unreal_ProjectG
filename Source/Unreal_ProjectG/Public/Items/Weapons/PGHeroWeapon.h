// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "Types/PGStructTypes.h"
#include "PGHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API APGHeroWeapon : public APGWeaponBase
{
	GENERATED_BODY()
	
public:
    FORCEINLINE const FPGHeroWeaponData& GetHeroWeaponData() const { return HeroWeaponData; }

protected:
    virtual void WeaponHitTargetHandler(AActor* HitActor) override;
    virtual void WeaponPulledFromTargetHandler(AActor* HitActor) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
    FPGHeroWeaponData HeroWeaponData;
};
