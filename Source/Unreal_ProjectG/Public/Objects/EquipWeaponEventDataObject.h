// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipWeaponEventDataObject.generated.h"

class APGWeaponBase;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UEquipWeaponEventDataObject : public UObject
{
	GENERATED_BODY()
	
public:
    void InitializeEquipWeaponEventData(TSubclassOf<APGWeaponBase> InEquippedWeaponClass)
    {
        EquippedWeaponClass = InEquippedWeaponClass;
    }

    FORCEINLINE TSubclassOf<APGWeaponBase> GetEquippedWeaponClass() const { return EquippedWeaponClass; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "EquipWeaponEventData")
    TSubclassOf<APGWeaponBase> EquippedWeaponClass;
};
