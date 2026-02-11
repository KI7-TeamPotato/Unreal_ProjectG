// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "UnitSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FUnitList
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<TWeakObjectPtr<AActor>> Units;
};

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UUnitSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    void RegisterUnit(AActor* Unit, FGameplayTag TeamTag);

    void UnregisterUnit(AActor* Unit, FGameplayTag TeamTag);

    const TArray<TWeakObjectPtr<AActor>>& GetUnitsByTeam(FGameplayTag TeamTag) const;

private:
    UPROPERTY()
    TMap<FGameplayTag, FUnitList> TeamUnitsMap;

    TArray<TWeakObjectPtr<AActor>> EmptyArray;
};
