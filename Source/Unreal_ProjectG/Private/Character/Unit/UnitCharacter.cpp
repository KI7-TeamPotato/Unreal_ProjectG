// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitCharacter.h"
#include "Components/Combat/UnitCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUp/DataAsset_UnitStartupData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "DataAssets/Unit/UnitData.h"

AUnitCharacter::AUnitCharacter()
{
    // AI 컨트롤러 빙의 시점 설정
    PrimaryActorTick.bCanEverTick = false;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    UnitCombatComponent = CreateDefaultSubobject<UUnitCombatComponent>(TEXT("UnitCombatComponent"));

    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        MovementComponent->bUseRVOAvoidance = false;
    }
}

UPawnCombatComponent* AUnitCharacter::GetPawnCombatComponent() const
{
    return UnitCombatComponent;
}



void AUnitCharacter::BeginPlay()
{
    Super::BeginPlay();

    AIController = Cast<AAIController>(GetController());
    //if (UUnitSubsystem* Subsystem = GetWorld()->GetSubsystem<UUnitSubsystem>())
    //{
    //    Subsystem->RegisterUnit(this, SideTag);
    //}
}

void AUnitCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    //if (UUnitSubsystem* Subsystem = GetWorld()->GetSubsystem<UUnitSubsystem>())
    // //{
    // //Subsystem->UnregisterUnit(this, SideTag);
    // //}

    Super::EndPlay(EndPlayReason);
}

void AUnitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUnitCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
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

                    UDataAsset_UnitStartupData* StartUpData = Cast<UDataAsset_UnitStartupData>(LoadedData);
                    //StartUpData = 이전 코드의 unitdata라고 생각하면 됩니다..
                    
                }
            }
        )
    );
}

void AUnitCharacter::SetAttackTarget(AActor* InTargetActor)
{
    TargetActor = InTargetActor;
    if (!AIController)
    {
        AIController = Cast<AAIController>(GetController());
    }

    if (AIController)
    {
        UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
        if (BBComp)
        {
            BBComp->SetValueAsObject(TEXT("AttackTarget"), InTargetActor);
        }
    }
}

void AUnitCharacter::Attack()
{
    //if (AttackMontage)
    //{
    //    PlayAnimMontage(AttackMontage);
    //}
}

void AUnitCharacter::ActivateUnit()
{
}

void AUnitCharacter::DeactivateUnit()
{
}