// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitPanel.generated.h"

class UUnitUIDataAsset;
class UUnitSlot;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UUnitPanel : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

public:
    // 에디터에서 5개의 유닛 데이터를 넣을 수 있는 배열
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Panel")
    TArray<TObjectPtr<UUnitUIDataAsset>> UnitDataList;

protected:
    // 유닛 슬롯 위젯
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUnitSlot> UnitSlot1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUnitSlot> UnitSlot2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUnitSlot> UnitSlot3;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUnitSlot> UnitSlot4;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUnitSlot> UnitSlot5;

private:
    // 슬롯들을 배열로 관리하기 위한 편의용 포인터 배열
    TArray<TObjectPtr<UUnitSlot>> SlotArray;
};
