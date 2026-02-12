// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScalableFloat.h"
#include "DataAsset_UnitBaseMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UDataAsset_UnitBaseMeleeAttack : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
    UPROPERTY(EditAnywhere, Category = "Ability|Attack")
    TArray<TObjectPtr<UAnimMontage>> AttackMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Attack")
    FScalableFloat AttackSkillMultiplier;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Attack")
    int32 MaxHitTargets = 1;
};
