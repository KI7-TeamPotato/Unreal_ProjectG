// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "EquipmentComponent.generated.h"

class APGWeaponBase;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECTG_API UEquipmentComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void SetCurrentEquippedWeapon(APGWeaponBase* NewWeapon);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    APGWeaponBase* GetCharacterCurrentEquippedWeapon() const { return CurrentEquippedWeapon.Get(); }

protected:
    UPROPERTY(VisibleAnywhere, Category = "Equipment|Data")
    TWeakObjectPtr<APGWeaponBase> CurrentEquippedWeapon;
};
