// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Types/PGStructTypes.h"
#include "UnitData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UUnitData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    // --- [1] 기본 정보 ---
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
    FGameplayTag ElementTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
    FGameplayTag TeamTag;

    UPROPERTY(EditAnywhere, Category = "Stats")
    UDataAsset* BranchData;

    // --- [2] 외형 ---
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    USkeletalMesh* SkeletalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    TSubclassOf<UAnimInstance> AnimBlueprint;
<<<<<<< HEAD
<<<<<<< Updated upstream

    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    //UAnimMontage* AttackMontage;

    //// --- [3] 능력치 (GAS 초기화용) ---
    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    //float Health = 100.0f;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    //float AttackDamage = 10.0f;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    //float MoveSpeed = 300.0f;
=======
>>>>>>> Stashed changes
=======


    // [추가] 유닛 등급 태그 (Unit.Tier.Normal, Unit.Tier.Rare 등 할당)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Tier")
    FGameplayTag UnitTier;

    // [추가] 중복 획득 시 지급할 조각 재화량 (노멀 10, 레어 50 등 기획자가 에디터에서 세팅)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Reward")
    int32 DuplicateRewardAmount = 10;
>>>>>>> e72f839c (UnitData,PGSaveGame,PGGameInstance 도감 관련 코드 수정 및 추가/PGUnitCollectionSubsystem  구성)
};
