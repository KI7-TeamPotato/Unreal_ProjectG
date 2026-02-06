// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitCharacter.h"
#include "Components/Combat/UnitCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUp/DataAsset_UnitStartupData.h"

AUnitCharacter::AUnitCharacter()
{
    // AI 컨트롤러 빙의 시점 설정
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    UnitCombatComponent = CreateDefaultSubobject<UUnitCombatComponent>(TEXT("UnitCombatComponent"));
}

UPawnCombatComponent* AUnitCharacter::GetPawnCombatComponent() const
{
    return UnitCombatComponent;
}

void AUnitCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AUnitCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitUnitStartUpData();
}

void AUnitCharacter::InitUnitStartUpData()
{
    if(CharacterStartupData.IsNull())
    {
        return;
    }

    // 비동기로 스타트업 데이터 로드 및 적용
    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        CharacterStartupData.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [this]()
            {
                if (UDataAsset_StartupDataBase* LoadedData = CharacterStartupData.Get())
                {
                    LoadedData->GiveToAbilitySystemComponent(PGAbilitySystemComponent);
                }
            }
        )
    );
}
