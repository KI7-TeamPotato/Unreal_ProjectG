// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UnitSpawnSubsystem.generated.h"
class AUnitCharacter;
class UDataAsset_UnitStartupData;

USTRUCT()
struct FUnitPoolList
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<TObjectPtr<AUnitCharacter>> Units;
};

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UUnitSpawnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void PrewarmPool(TSubclassOf<AUnitCharacter> UnitClass, int32 Count);

    UFUNCTION(BlueprintCallable)
    void GetFromPool(TSubclassOf<AUnitCharacter> UnitClass);

    UFUNCTION(BlueprintCallable)
    void ReturnToPool(TSubclassOf<AUnitCharacter> Unit);

    UFUNCTION(BlueprintCallable)
    void SpawnUnit(TSoftObjectPtr<UDataAsset_UnitStartupData> UnitData, 
        FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable)
    void GetAllActiveUnits(TArray<AUnitCharacter*>& OutUnits);

    UFUNCTION(BlueprintCallable)
    void DespawnAllActiveUnits();

    UFUNCTION(BlueprintCallable)
    void OnUnitDied(AUnitCharacter* Victim);

    UPROPERTY()
    TMap<TSubclassOf<AUnitCharacter>, FUnitPoolList> PoolStorage;
private:
    UPROPERTY()
    TArray<TWeakObjectPtr<AUnitCharacter>> ActiveUnits;

    UPROPERTY()
    TArray<TWeakObjectPtr<AActor>> EmptyArray;
};
