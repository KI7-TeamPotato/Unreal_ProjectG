// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PGBaseAnimInstance.h"
#include "PGHeroLinkedAnimLayer.generated.h"

class UPGHeroAnimInstance;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPGHeroLinkedAnimLayer : public UPGBaseAnimInstance
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    UPGHeroAnimInstance* GetHeroAnimInstance() const;
};
