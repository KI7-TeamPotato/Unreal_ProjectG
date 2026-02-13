// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "Types/PGEnumTypes.h"
#include "BTD_ChackState.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UBTD_ChackState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
    UBTD_ChackState();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
    UPROPERTY(EditAnywhere, Category = "Condition")
    EUnitState TargetState;
};
