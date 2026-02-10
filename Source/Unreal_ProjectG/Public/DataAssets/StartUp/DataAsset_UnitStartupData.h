// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/DataAsset_StartupDataBase.h"
#include "DataAsset_UnitStartupData.generated.h"

class UPGUnitGameplayAbility;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UDataAsset_UnitStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
    virtual void GiveToAbilitySystemComponent(UPGAbilitySystemComponent* InASCToGive, int32 InLevel = 1) override;

public:
    UPROPERTY(EditDefaultsOnly, Category = "StartupData|Visual")
    TObjectPtr<UAnimMontage> AttackMontage;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StartupData")
    TArray<TSubclassOf<UPGUnitGameplayAbility>> UnitCombatAbilities;
};
