// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Battle/UnitSlotWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DataAssets/UI/UnitUIDataAsset.h"
<<<<<<< Updated upstream
=======
#include "Character/Hero/HeroCharacter.h"
#include "Pawn/BaseStructure.h"
#include "Kismet/GameplayStatics.h"
#include "Mode/Save/PGGameInstance.h"
>>>>>>> Stashed changes

void UUnitSlotWidget::InitializeSlot(UUnitUIDataAsset* InDataAsset)
{
    if (!InDataAsset) return;

    UnitData = InDataAsset;

    // 텍스트 설정
    if (UnitCost)
    {
        UnitCost->SetText(FText::AsNumber(UnitData->UnitCost));
    }

    // 버튼 이미지 설정
    FButtonStyle NewStyle = UnitButton->GetStyle();

    if (UnitData->UnitButtonNormalImage)
    {
        NewStyle.Normal.SetResourceObject(UnitData->UnitButtonNormalImage);
        NewStyle.Hovered.SetResourceObject(UnitData->UnitButtonNormalImage);
    }

    if (UnitData->UnitButtonPressedImage)
        NewStyle.Pressed.SetResourceObject(UnitData->UnitButtonPressedImage);

    if (UnitData->UnitButtonUnableImage)
        NewStyle.Disabled.SetResourceObject(UnitData->UnitButtonUnableImage);

    UnitButton->SetStyle(NewStyle);
}

void UUnitSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UnitButton)
    {
        UnitButton->OnClicked.AddDynamic(this, &UUnitSlotWidget::OnUnitButtonClicked);
    }
}

void UUnitSlotWidget::OnUnitButtonClicked()
{
    if (!UnitData || !UnitData->UnitClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("UnitData or UnitClass is null!"));
        return;
    }

    FVector SpawnLocation = FVector(0.0f, 0.0f, 100.0f);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    FActorSpawnParameters SpawnParams;

    // 유닛 스폰
    GetWorld()->SpawnActor<AUnitCharacter>(UnitData->UnitClass, SpawnLocation, SpawnRotation, SpawnParams);

<<<<<<< Updated upstream
    UE_LOG(LogTemp, Log, TEXT("Spawned Unit: %s"), *UnitData->UnitClass->GetName());
=======
        // 유닛 인스턴스 생성
        AUnitCharacter* NewUnit = GetWorld()->SpawnActorDeferred<AUnitCharacter>(
            UnitData->UnitClass,
            FTransform(SpawnRotation, RandomLocation),
            nullptr, nullptr,
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn
        );

        if (NewUnit)
        {
            int32 TargetID = UnitData->UnitID;
            int32 TargetLevel = 1;
            UPGGameInstance* GI = Cast<UPGGameInstance>(GetGameInstance());
          
            if (FUnitSaveData* FoundData = GI->UnitLevelMap.Find(TargetID))
            {
                // 유닛이 해금된 상태인지 확인 후 레벨 적용
                if (FoundData->bIsUnlocked)
                {
                    TargetLevel = FoundData->Level;
                }
            }
            NewUnit->UnitLevel = TargetLevel;

            // 인스턴스를 바탕으로 유닛 스폰
            NewUnit->FinishSpawning(FTransform(SpawnRotation, RandomLocation));

            UE_LOG(LogTemp, Log, TEXT("Spawned Unit: %d with Level: %d"), UnitData->UnitID, TargetLevel);
        }
    }
>>>>>>> Stashed changes
}

