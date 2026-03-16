// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PGSaveGame.generated.h"

/**
 * 게임의 로컬 세이브 데이터를 담당하는 클래스
 */
UCLASS()
class UNREAL_PROJECTG_API UPGSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPGSaveGame();

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    FString PlayerName;

    // --- [재화 관련] ---
    UPROPERTY(VisibleAnywhere, Category = "Basic")
    int32 PlayerGold;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    int32 PlayerGem;

    // [추가됨] 가챠 중복 획득 시 얻는 조각 재화
    UPROPERTY(VisibleAnywhere, Category = "Basic")
    int32 PlayerUnlock;

    // --- [장착 데이터] ---
    UPROPERTY(VisibleAnywhere, Category = "Equipment")
    FSoftObjectPath EquippedWeaponPath;

    UPROPERTY(VisibleAnywhere, Category = "Equipment")
    FSoftObjectPath EquippedArmorPath;

    UPROPERTY(VisibleAnywhere, Category = "Equipment")
    FSoftObjectPath EquippedAccessoryPath;

    // 장착 중인 유닛(최대 5개) 데이터 에셋의 경로들
    UPROPERTY(VisibleAnywhere, Category = "Equipment")
    TArray<FSoftObjectPath> EquippedUnitPaths;

    // --- [도감 데이터] ---
    // [추가] 해금(보유)한 모든 유닛 목록
    UPROPERTY(VisibleAnywhere, Category = "Collection")
    TArray<FSoftObjectPath> OwnedUnitPaths;
};