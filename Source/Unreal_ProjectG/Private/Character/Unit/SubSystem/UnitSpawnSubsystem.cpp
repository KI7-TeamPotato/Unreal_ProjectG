// UnitSpawnSubsystem.cpp

#include "Character/Unit/SubSystem/UnitSpawnSubsystem.h"
#include "Character/Unit/UnitCharacter.h"
#include "Engine/World.h"
#include "DataAssets/StartUp/DataAsset_UnitStartupData.h"

void UUnitSpawnSubsystem::PrewarmPool(TSubclassOf<AUnitCharacter> UnitClass, int32 Count)
{
    if (!GetWorld() || !UnitClass) return;

    FUnitPoolList& PoolList = PoolStorage.FindOrAdd(UnitClass);
    int32 CurrentCount = PoolList.Units.Num();
    int32 NeededCount = Count - CurrentCount;

    if (NeededCount <= 0) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < NeededCount; i++)
    {
        AUnitCharacter* NewUnit = GetWorld()->SpawnActor<AUnitCharacter>(UnitClass, FVector(0, 0, -10000.0f), FRotator::ZeroRotator, SpawnParams);
        if (NewUnit)
        {
            NewUnit->DeactivateUnit();
            PoolList.Units.Add(NewUnit);
        }
    }
}

// [추가 구현] 헤더에 선언된 private 함수 구현
AUnitCharacter* UUnitSpawnSubsystem::GetUnitInstance(TSubclassOf<AUnitCharacter> UnitClass)
{
    if (!UnitClass || !GetWorld()) return nullptr;

    FUnitPoolList& PoolList = PoolStorage.FindOrAdd(UnitClass);
    AUnitCharacter* UnitToReturn = nullptr;

    // 1. 풀에서 유효한 유닛 찾기
    while (PoolList.Units.Num() > 0)
    {
        UnitToReturn = PoolList.Units.Pop();
        if (IsValid(UnitToReturn))
        {
            break;
        }
        UnitToReturn = nullptr;
    }

    // 2. 없으면 새로 생성
    if (!UnitToReturn)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        UnitToReturn = GetWorld()->SpawnActor<AUnitCharacter>(UnitClass, FVector(0, 0, -10000.0f), FRotator::ZeroRotator, SpawnParams);
    }

    return UnitToReturn;
}

// [수정] 인자를 UnitClass와 UnitData 모두 받도록 변경
void UUnitSpawnSubsystem::SpawnUnit(TSubclassOf<AUnitCharacter> UnitClass, TSoftObjectPtr<UDataAsset_UnitStartupData> UnitData, FVector Location, FRotator Rotation)
{
    if (!UnitClass) return;

    AUnitCharacter* SpawnedUnit = GetUnitInstance(UnitClass);

    if (SpawnedUnit)
    {
        SpawnedUnit->SetActorLocationAndRotation(Location, Rotation);

        // [수정] 직접 접근 대신 Setter 사용 (Error C2248 해결)
        SpawnedUnit->SetCharacterStartupData(UnitData);

        ActiveUnits.Add(SpawnedUnit);
        SpawnedUnit->ActivateUnit();
    }
}

// [수정] 인자를 AUnitCharacter* 로 변경
void UUnitSpawnSubsystem::ReturnToPool(AUnitCharacter* Unit)
{
    if (!IsValid(Unit)) return;

    Unit->DeactivateUnit();

    // 유닛의 클래스를 키값으로 사용하여 풀에 저장
    TSubclassOf<AUnitCharacter> UnitClass = Unit->GetClass();
    FUnitPoolList& PoolList = PoolStorage.FindOrAdd(UnitClass);

    PoolList.Units.Add(Unit);

    // 활성 목록에서 제거
    ActiveUnits.RemoveAll([Unit](const TWeakObjectPtr<AUnitCharacter>& Ptr)
        {
            return !Ptr.IsValid() || Ptr.Get() == Unit;
        });
}

void UUnitSpawnSubsystem::GetAllActiveUnits(TArray<AUnitCharacter*>& OutUnits)
{
    OutUnits.Empty();
    for (int32 i = ActiveUnits.Num() - 1; i >= 0; --i)
    {
        if (ActiveUnits[i].IsValid())
        {
            OutUnits.Add(ActiveUnits[i].Get());
        }
        else
        {
            ActiveUnits.RemoveAt(i);
        }
    }
}

void UUnitSpawnSubsystem::DespawnAllActiveUnits()
{
    // 복사본을 만들어 순회 (ReturnToPool 내부에서 ActiveUnits를 수정하므로)
    TArray<TWeakObjectPtr<AUnitCharacter>> TempUnits = ActiveUnits;

    for (const auto& WeakUnit : TempUnits)
    {
        if (AUnitCharacter* Unit = WeakUnit.Get())
        {
            ReturnToPool(Unit);
        }
    }
    ActiveUnits.Empty();
}

void UUnitSpawnSubsystem::OnUnitDied(AUnitCharacter* Victim)
{
    if (IsValid(Victim))
    {
        // Destroy 대신 풀 반환 호출
        ReturnToPool(Victim);
    }
}