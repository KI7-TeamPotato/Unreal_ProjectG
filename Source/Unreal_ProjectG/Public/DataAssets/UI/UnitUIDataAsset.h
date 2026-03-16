// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/Unit/UnitCharacter.h"
#include "UnitUIDataAsset.generated.h"

/**
 * 
 */
<<<<<<< Updated upstream
UCLASS()
class UNREAL_PROJECTG_API UUnitUIDataAsset : public UDataAsset
=======
UCLASS(BlueprintType)
class UNREAL_PROJECTG_API UUnitUIDataAsset : public UPrimaryDataAsset
>>>>>>> Stashed changes
{
	GENERATED_BODY()
	
public:
    // 유닛 캐릭터 블루프린트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    TSubclassOf<AUnitCharacter> UnitClass;

    // 유닛 버튼 일반 이미지
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    TObjectPtr<UTexture2D> UnitButtonNormalImage;

    // 유닛 버튼 눌림 이미지
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    TObjectPtr<UTexture2D> UnitButtonPressedImage;

    // 유닛 버튼 비활성화 이미지
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    TObjectPtr<UTexture2D> UnitButtonUnableImage;

    // 유닛 코스트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    int32 UnitCost;

  // ==========================================================
  // --- [가챠/도감 시스템을 위해 추가된 정보들] ---
  // ==========================================================

  // 유닛 등급 태그 (예: Unit.Tier.Normal, Unit.Tier.Rare 등 할당)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Collection")
    FGameplayTag UnitTier;

    // 중복 획득 시 지급할 조각 재화량 (기획자가 에디터에서 등급별로 다르게 세팅)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Collection")
    int32 DuplicateRewardAmount = 10;
};
