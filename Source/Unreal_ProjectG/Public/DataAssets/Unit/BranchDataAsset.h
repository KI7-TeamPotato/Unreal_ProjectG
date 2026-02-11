// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "BranchDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UBranchDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DetectRange = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange = 250.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
    FGameplayTag BranchTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TObjectPtr<class UBehaviorTree> SubBTAsset;
};
