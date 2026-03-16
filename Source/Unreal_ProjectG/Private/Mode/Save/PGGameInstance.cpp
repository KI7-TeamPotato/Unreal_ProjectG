#include "Mode/Save/PGGameInstance.h"
#include "Mode/Save/PGUnitCollectionSubsystem.h"
#include "Mode/Save/PGSaveGame.h"
#include "Mode/Save/PGUnitCollectionSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "DataAssets/UI/UnitUIDataAsset.h"
<<<<<<< Updated upstream
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
#include "UI/Battle/BattleHUD.h"
#include "UI/DataTable/UnitUIDataTable.h"
>>>>>>> Stashed changes
=======
#include "DataAssets/UI/EquipUIDataAsset.h"
#include "UI/Battle/BattleHUD.h"
>>>>>>> e72f839c (UnitData,PGSaveGame,PGGameInstance 도감 관련 코드 수정 및 추가/PGUnitCollectionSubsystem  구성)
=======
#include "DataAssets/UI/EquipUIDataAsset.h"
#include "UI/Battle/BattleHUD.h"
>>>>>>> Stashed changes


//------- 구현 방식 ----------
//세이브 및 인스턴스 구현 방식: UI 버튼 클릭 이벤트 함수 내부 어딘가
//if (UPGGameInstance* GI = Cast<UPGGameInstance>(GetGameInstance()))
//{
//    GI->CurrentWeapon = SelectedWeapon; // 1. 바꾼 무기 적용
//    GI->SaveGameData();                 // 2. 즉시 디스크에 자동 저장!
//}

// PGBaseGameMode.cpp 의 OnGameOver 함수 내부
//if (bIsPlayerVictory)
//{
//    // ... 별점 계산 및 골드 지급 로직 ...
//
//    if (UPGGameInstance* GI = Cast<UPGGameInstance>(GetGameInstance()))
//    {
//        GI->SaveGameData(); // 획득한 골드와 진행도를 자동 저장!
//    }
//}

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
<<<<<<< HEAD
<<<<<<< Updated upstream
    }

    // 디스크 데이터(Path) -> 런타임 데이터(SoftPtr) 로드
    //장비
    CurrentWeapon = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedWeaponPath);
    CurrentArmor = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedArmorPath);
    CurrentAccessory = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedAccessoryPath);

    //재화
    CurrentPlayerGold = CachedSaveData->PlayerGold;
<<<<<<< Updated upstream
    CurrentPlayerRuby = CachedSaveData->PlayerRuby;
    CurrentPlayerPiece = CachedSaveData->PlayerPiece;
=======
        InitializeUnitMap();
    }

    // 테스트용 유닛 맵 초기화
    InitializeUnitMap();

    // 디스크 데이터(Path) -> 런타임 데이터(SoftPtr) 로드
    //장비
    CurrentWeapon = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedWeaponPath);
    CurrentArmor = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedArmorPath);
    CurrentAccessory = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedAccessoryPath);

    //재화
    CurrentPlayerGold = CachedSaveData->PlayerGold;
    CurrentPlayerGem = CachedSaveData->PlayerGem;
    CurrentPlayerUnlock = CachedSaveData->PlayerUnlock;
>>>>>>> Stashed changes
=======
    CurrentPlayerGem = CachedSaveData->PlayerGem;
    CurrentPlayerUnlock = CachedSaveData->PlayerUnlock;
>>>>>>> Stashed changes

    CurrentUnits.Empty();
    for (const FSoftObjectPath& Path : CachedSaveData->EquippedUnitPaths)
    {
        CurrentUnits.Add(TSoftObjectPtr<UUnitUIDataAsset>(Path));
<<<<<<< Updated upstream
=======
    }
}
=======
    }  

    if (CachedSaveData)
    {
        // 디스크 데이터(Path) -> 런타임 데이터(SoftPtr) 로드
        //장비
        CurrentWeapon = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedWeaponPath);
        CurrentArmor = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedArmorPath);
        CurrentAccessory = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedAccessoryPath);
>>>>>>> e72f839c (UnitData,PGSaveGame,PGGameInstance 도감 관련 코드 수정 및 추가/PGUnitCollectionSubsystem  구성)

        //재화
        CurrentPlayerGold = CachedSaveData->PlayerGold;
        CurrentPlayerGem = CachedSaveData->PlayerGem;
        CurrentPlayerUnlock = CachedSaveData->PlayerUnlock; // 조각 재화 로드

        // 기존 방식의 CurrentUnits 배열 복구 (UI 등에서 직접 참조하는 경우를 위함)
        CurrentUnits.Empty();
        for (const FSoftObjectPath& Path : CachedSaveData->EquippedUnitPaths)
        {
            CurrentUnits.Add(TSoftObjectPtr<UUnitUIDataAsset>(Path));
        }

        //[추가] 서브시스템에 세이브 데이터 전달하여 도감 상태 복구
        if (UUnitCollectionSubsystem* CollectionSubsystem = GetSubsystem<UUnitCollectionSubsystem>())
        {
            CollectionSubsystem->LoadFromSaveGame(CachedSaveData);
        }
>>>>>>> Stashed changes
    }

    if (CachedSaveData)
    {
        // 디스크 데이터(Path) -> 런타임 데이터(SoftPtr) 로드
        //장비
        CurrentWeapon = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedWeaponPath);
        CurrentArmor = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedArmorPath);
        CurrentAccessory = TSoftObjectPtr<UEquipUIDataAsset>(CachedSaveData->EquippedAccessoryPath);

        //재화
        CurrentPlayerGold = CachedSaveData->PlayerGold;
        CurrentPlayerGem = CachedSaveData->PlayerGem;
        CurrentPlayerUnlock = CachedSaveData->PlayerUnlock; // 조각 재화 로드

        // 기존 방식의 CurrentUnits 배열 복구 (UI 등에서 직접 참조하는 경우를 위함)
        CurrentUnits.Empty();
        for (const FSoftObjectPath& Path : CachedSaveData->EquippedUnitPaths)
        {
            CurrentUnits.Add(TSoftObjectPtr<UUnitUIDataAsset>(Path));
        }

        // [추가] 서브시스템에 세이브 데이터 전달하여 도감/파티 상태 복구
        if (UPGUnitCollectionSubsystem* CollectionSubsystem = GetSubsystem<UPGUnitCollectionSubsystem>())
        {
            CollectionSubsystem->LoadFromSaveGame(CachedSaveData);
        }
    }
}

void UPGGameInstance::SaveGameData()
{
    if (!CachedSaveData) return;

    // 런타임 데이터(SoftPtr) -> 디스크 데이터(Path) 저장
    // 게임 중 변동된 장비를 세이브 파일에 덮어쓰기
    CachedSaveData->EquippedWeaponPath = CurrentWeapon.ToSoftObjectPath();
    CachedSaveData->EquippedArmorPath = CurrentArmor.ToSoftObjectPath();
    CachedSaveData->EquippedAccessoryPath = CurrentAccessory.ToSoftObjectPath();

    // 게임 중 변동된 재화를 세이브 파일에 덮어쓰기
    CachedSaveData->PlayerGold = CurrentPlayerGold;
    CachedSaveData->PlayerGem = CurrentPlayerGem;
    CachedSaveData->PlayerUnlock = CurrentPlayerUnlock;

    CachedSaveData->EquippedUnitPaths.Empty();
    for (const auto& UnitPtr : CurrentUnits)
    {
        CachedSaveData->EquippedUnitPaths.Add(UnitPtr.ToSoftObjectPath());
    }

<<<<<<< Updated upstream
    //[추가] 서브시스템의 최신 도감상태를 CachedSaveData에 덮어씌움
    if (UUnitCollectionSubsystem* CollectionSubsystem = GetSubsystem<UUnitCollectionSubsystem>())
=======
    //[추가] 도감 저장 서브시스템의 최신 도감(보유 유닛) 상태를 저장
    if (UPGUnitCollectionSubsystem* CollectionSubsystem = GetSubsystem<UPGUnitCollectionSubsystem>())
>>>>>>> Stashed changes
    {
        CollectionSubsystem->SaveToSaveGame(CachedSaveData);
    }

<<<<<<< Updated upstream
    // 4. 디스크에 최종 저장
=======
>>>>>>> Stashed changes
    UGameplayStatics::SaveGameToSlot(CachedSaveData, SaveSlotName, 0);
}