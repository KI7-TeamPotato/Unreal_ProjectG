// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/AI/UnitDetourCrowdAIController.h"
#include "Character/Unit/UnitCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AUnitDetourCrowdAIController::AUnitDetourCrowdAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AUnitDetourCrowdAIController::OnPossess(APawn* InPawn)
{

    /*지금 방식은 비동기 로딩이 끝나기 전에 빙의하기 때문에 작동 안될 가능성이 높음.
    제미나이 물어보니 델리게이트를 이용하라 하는데 이건 내일 한번 상의해야 할듯???*/
    
    Super::OnPossess(InPawn);

    AUnitCharacter* Unit = Cast<AUnitCharacter>(InPawn);
    if (Unit && GetBlackboardComponent())
    {
        GetBlackboardComponent()->SetValueAsFloat(TEXT("Range"), Unit->GetDetectRangeKey());
        GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), Unit->GetAttackRangeKey());
    }

    UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
    if (CrowdComp)
    {
        CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
    }

    if (BTAsset)
    {
        if (RunBehaviorTree(BTAsset))
        {
            UE_LOG(LogTemp, Log, TEXT("메인 BT 실행 성공"));
            SetUnitState(EUnitState::Move);

            AUnitCharacter* CrowdUnit = Cast<AUnitCharacter>(InPawn);
            if (CrowdUnit && CrowdUnit->GetSubBTAssetKey())
            {
                UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
                if (BTComp)
                {
                    FGameplayTag CombatTag = FGameplayTag::RequestGameplayTag(TEXT("AI.State.Combat"));
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("FailRunBehaviorTree"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("BTAssetNull"));
    }
}

void AUnitDetourCrowdAIController::OnUnPossess()
{
    if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
    {
        BTComp->StopTree(EBTStopMode::Safe);
    }

    Super::OnUnPossess();
}

FGenericTeamId AUnitDetourCrowdAIController::GetGenericTeamId() const
{
    return FGenericTeamId();
}

void AUnitDetourCrowdAIController::SetUnitState(EUnitState NewState)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(NewState));
        UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
        if (CrowdComp)
        {
            if (NewState == EUnitState::Combat)
            {
                //CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);

            }
            else if (NewState == EUnitState::Dead)
            {
                CrowdComp->SetCrowdSimulationState(ECrowdSimulationState::Disabled);
            }
            else
            {
                CrowdComp->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
                CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
            }
        }
    }
}
