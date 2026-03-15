// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/Unit/UnitCharacter.h"
#include "PGGameInstance.generated.h"

class UPGSaveGame;
class UDataAsset_WeaponData;
class UDataAsset_ArmorData;
class UDataAsset_AccessoryData;
class UUnitUIDataAsset;

USTRUCT(BlueprintType)
struct FUnitSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;        // 유닛 레벨

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked = false; // 보유 여부
};

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

protected:
    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void InitializeUnitMap();

public:
    FUnitSaveData GetUnitSaveData(int32 UnitID);

    // --- [런타임 장착 데이터] ---
    // 로비 UI에서 이 변수들을 수정하고, 전투 맵에서 이 변수들을 읽어 적용
    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_WeaponData> CurrentWeapon;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_ArmorData> CurrentArmor;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TSoftObjectPtr<UDataAsset_AccessoryData> CurrentAccessory;

    UPROPERTY(BlueprintReadWrite, Category = "Equipment")
    TArray<TSoftObjectPtr<UUnitUIDataAsset>> CurrentUnits;

    //소지 재화
    UPROPERTY(BlueprintReadWrite, Category = "Player Info")
    int32 CurrentPlayerGold;

    UPROPERTY(BlueprintReadWrite, Category = "Player Info")
    int32 CurrentPlayerRuby;

    UPROPERTY(BlueprintReadWrite, Category = "Player Info")
    int32 CurrentPlayerPiece;

<<<<<<< Updated upstream
=======
    //스테이지
    UPROPERTY(BlueprintReadWrite, Category = "Player Info")
    int32 CurrentStageIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
    TMap<int32, FUnitSaveData> UnitLevelMap;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    TObjectPtr<UDataTable> UnitDataTable;

>>>>>>> Stashed changes
private:
    UPROPERTY()
    TObjectPtr<UPGSaveGame> CachedSaveData;

    FString SaveSlotName = TEXT("PG_SaveSlot_01");
};
