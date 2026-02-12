// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/SubSystem/UnitSpawnSubsystem.h"
#include "Character/Unit/UnitCharacter.h"
#include "Engine/World.h"

void UUnitSpawnSubsystem::PrewarmPool(TSubclassOf<AUnitCharacter> UnitClass, int32 Count)
{
    if (!GetWorld() || !UnitClass)
    {
        return;
    }
    FUnitPoolList& PoolList = PoolStorage.FindOrAdd(UnitClass);

    int32 NeededCount = Count - PoolList.Units.Num();

    FActorSpawnParameters SpawnParams;

    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < NeededCount; i++)
    {
        AUnitCharacter* NewUnit = GetWorld()->SpawnActor<AUnitCharacter>(UnitClass,
            FVector(0, 0, -10000.0f),
            FRotator::ZeroRotator,
            SpawnParams
        );
        if (NewUnit)
        {
            NewUnit->DeactivateUnit();
            PoolList.Units.Add(NewUnit);
        }
    }
}

void UUnitSpawnSubsystem::GetFromPool(TSubclassOf<AUnitCharacter> UnitClass)
{

}

void UUnitSpawnSubsystem::ReturnToPool(TSubclassOf<AUnitCharacter> Unit)
{
}

void UUnitSpawnSubsystem::SpawnUnit(TSoftObjectPtr<UDataAsset_UnitStartupData> UnitData, FVector Location, FRotator Rotation)
{
}

void UUnitSpawnSubsystem::GetAllActiveUnits(TArray<AUnitCharacter*>& OutUnits)
{ 
}

void UUnitSpawnSubsystem::DespawnAllActiveUnits()
{
}

void UUnitSpawnSubsystem::OnUnitDied(AUnitCharacter* Victim)
{
}
