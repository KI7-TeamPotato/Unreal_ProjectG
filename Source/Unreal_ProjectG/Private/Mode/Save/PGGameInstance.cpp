#include "Mode/Save/PGGameInstance.h"
#include "Mode/Save/PGSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DataAssets/Items/DataAsset_WeaponData.h"
#include "DataAssets/UI/UnitUIDataAsset.h"

void UPGGameInstance::Init()
{
    Super::Init();
    LoadGameData();
}

void UPGGameInstance::LoadGameData()
{
    // 세이브 파일이 있으면 불러오고, 없으면 새로 생성
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
    {
        CachedSaveData = Cast<UPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    }
    else
    {
        CachedSaveData = Cast<UPGSaveGame>(UGameplayStatics::CreateSaveGameObject(UPGSaveGame::StaticClass()));
    }

    // 디스크 데이터(Path) -> 런타임 데이터(SoftPtr) 로드
    CurrentWeapon = TSoftObjectPtr<UDataAsset_WeaponData>(CachedSaveData->EquippedWeaponPath);

    CurrentUnits.Empty();
    for (const FSoftObjectPath& Path : CachedSaveData->EquippedUnitPaths)
    {
        CurrentUnits.Add(TSoftObjectPtr<UUnitUIDataAsset>(Path));
    }
}

void UPGGameInstance::SaveGameData()
{
    if (!CachedSaveData) return;

    // 런타임 데이터(SoftPtr) -> 디스크 데이터(Path) 저장
    CachedSaveData->EquippedWeaponPath = CurrentWeapon.ToSoftObjectPath();

    CachedSaveData->EquippedUnitPaths.Empty();
    for (const auto& UnitPtr : CurrentUnits)
    {
        CachedSaveData->EquippedUnitPaths.Add(UnitPtr.ToSoftObjectPath());
    }

    UGameplayStatics::SaveGameToSlot(CachedSaveData, SaveSlotName, 0);
}