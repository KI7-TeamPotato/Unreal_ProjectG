// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "EquipmentComponent.generated.h"


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECTG_API UEquipmentComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

};