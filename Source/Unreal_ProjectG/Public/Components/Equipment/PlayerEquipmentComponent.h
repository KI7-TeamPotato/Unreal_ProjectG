// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Equipment/EquipmentComponent.h"
#include "PlayerEquipmentComponent.generated.h"

class APGPlayerWeapon;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPlayerEquipmentComponent : public UEquipmentComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "PG|Equipment")
    APGPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;
};
