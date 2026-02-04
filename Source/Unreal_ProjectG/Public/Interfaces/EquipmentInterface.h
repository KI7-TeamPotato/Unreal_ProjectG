// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentInterface.generated.h"

class UEquipmentComponent;
class UHeroEquipmentComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquipmentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREAL_PROJECTG_API IEquipmentInterface
{
	GENERATED_BODY()

public:
    virtual UEquipmentComponent* GetEquipmentComponent() const = 0;  
};
