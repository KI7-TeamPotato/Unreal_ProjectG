// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "PGPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API APGPlayerWeapon : public APGWeaponBase
{
	GENERATED_BODY()
	
protected:
    virtual void WeaponHitTargetHandler(AActor* HitActor) override;
    virtual void WeaponPulledFromTargetHandler(AActor* HitActor) override;
};
