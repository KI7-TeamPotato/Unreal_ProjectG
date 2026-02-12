// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/DataAsset_StartupDataBase.h"
#include "ScalableFloat.h"
#include "DataAsset_UnitStartupData.generated.h"

class UPGUnitGameplayAbility;
class UDataAsset_UnitBaseMeleeAttack;

USTRUCT(BlueprintType)
struct FPGUnitAbilitySet
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Attack")
    TSubclassOf<UPGUnitGameplayAbility> UnitCombatAbility;

    UPROPERTY(EditAnywhere, Category = "Ability|Attack")
    TArray<TObjectPtr<UAnimMontage>> AttackMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Attack")
    FScalableFloat AttackSkillMultiplier;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Attack")
    int32 MaxHitTargets = 1;
    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    //TObjectPtr<UDataAsset_UnitBaseMeleeAttack> 
};

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UDataAsset_UnitStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
    virtual void GiveToAbilitySystemComponent(UPGAbilitySystemComponent* InASCToGive, int32 InLevel = 1) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StartupData")
    TArray<TSubclassOf<UPGUnitGameplayAbility>> UnitCombatAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "StartupData")
    TArray<FPGUnitAbilitySet> UnitAbilitySets;
};
