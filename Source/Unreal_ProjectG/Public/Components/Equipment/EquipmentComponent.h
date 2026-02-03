// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "EquipmentComponent.generated.h"

class APGWeaponBase;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UEquipmentComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
    APGWeaponBase* GetCharacterCurrentEquippedWeapon() const { return CurrentEquippedWeapon.Get(); }

protected:
    TWeakObjectPtr<APGWeaponBase> CurrentEquippedWeapon;
};
