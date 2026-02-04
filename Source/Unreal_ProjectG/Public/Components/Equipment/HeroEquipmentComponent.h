// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Equipment/EquipmentComponent.h"
#include "HeroEquipmentComponent.generated.h"

class APGHeroWeapon;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UHeroEquipmentComponent : public UEquipmentComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "PG|Equipment")
    APGHeroWeapon* GetHeroCurrentEquippedWeapon() const;
};
