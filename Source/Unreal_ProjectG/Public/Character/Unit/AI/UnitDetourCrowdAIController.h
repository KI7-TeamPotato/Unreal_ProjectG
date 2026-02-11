// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "Types/PGEnumTypes.h"
#include "UnitDetourCrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API AUnitDetourCrowdAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
public:
    AUnitDetourCrowdAIController(const FObjectInitializer& ObjectInitializer);

protected:

    //빙의(Possess)될 때 호출됨.(유닛 스폰 시점)
    virtual void OnPossess(APawn* InPawn) override;

    //빙의 해제될 때(유닛 사망, 풀반납)
    virtual void OnUnPossess() override;

public:
    virtual FGenericTeamId GetGenericTeamId() const override;

    void InitializeAI();

public:
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetUnitState(EUnitState NewState);

private:
    UPROPERTY(EditAnywhere, Category = "AI")
    TObjectPtr<class UBehaviorTree> BTAsset;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    TObjectPtr<class UBlackboardComponent> BlackboardComp;

    const FName StateKeyName = TEXT("State");

    FGenericTeamId CachedTeamId;
};
