// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API URangeCheck : public UBTService
{
	GENERATED_BODY()
public:
    URangeCheck();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
    UPROPERTY(EditAnywhere, Category = "AI|Optimization")
    float StickinessMultiplier = 1.2f;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector DetectRangeKey;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector AttackRangeKey;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector TargetActorKey;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector IsInDetectRangeKey;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector IsInAttackRangeKey;
};
