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
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Melee Attack")
    TArray<TObjectPtr<UAnimMontage>> MeleeAttackMontages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Melee Attack")
    FScalableFloat MeleeAttackSkillMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Melee Attack")
    float MeleeAttackDamageRadius = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Melee Attack")
    int32 MaxHitTargets = 1;
};
