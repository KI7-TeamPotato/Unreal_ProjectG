// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PGGameInstance.generated.h"

class UPGSaveGame;
class UDataAsset_WeaponData;
class UUnitUIDataAsset;

UCLASS()
class UNREAL_PROJECTG_API UPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    virtual void Init() override;

    // --- [Save/Load 시스템] ---
    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    void SaveGameData();

    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    void LoadGameData();

    // --- [런타임 장착 데이터] ---
    // 로비 UI에서 이 변수들을 수정하고, 전투 맵에서 이 변수들을 읽어 적용
    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_WeaponData> CurrentWeapon;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_WeaponData> CurrentArmor;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_WeaponData> CurrentAccessory;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TArray<TSoftObjectPtr<UUnitUIDataAsset>> CurrentUnits;

private:
    UPROPERTY()
    TObjectPtr<UPGSaveGame> CachedSaveData;

    FString SaveSlotName = TEXT("PG_SaveSlot_01");
};
