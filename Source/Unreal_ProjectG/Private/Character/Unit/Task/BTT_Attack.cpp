// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/Task/BTT_Attack.h"
#include "AIController.h"
#include "Character/Unit/UnitCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_Attack::UBTT_Attack()
{
    NodeName = "Attack";
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    AUnitCharacter* Unit = Cast<AUnitCharacter>(AIC->GetPawn());
    if (!Unit) return EBTNodeResult::Failed;

   // Unit->Attack();

    return EBTNodeResult::Succeeded;
}
