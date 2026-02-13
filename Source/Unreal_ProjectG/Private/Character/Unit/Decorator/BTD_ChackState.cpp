// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/Decorator/BTD_ChackState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_ChackState::UBTD_ChackState()
{
    NodeName = TEXT("Check Unit State");

    BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTD_ChackState, TargetState), StaticEnum<EUnitState>());
}

bool UBTD_ChackState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return false;

    uint8 CurrentState = BB->GetValueAsEnum(GetSelectedBlackboardKey());

    return CurrentState == static_cast<uint8>(TargetState);
}
