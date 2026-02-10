// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PGCharacterBase.h"
#include "NativeGameplayTags.h"
#include "GameplayTagAssetInterface.h"
#include "UnitCharacter.generated.h"

class UBehaviorTree;
class UUnitData;
class UUnitCombatComponent;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API AUnitCharacter : public APGCharacterBase, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:
    AUnitCharacter();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
    // 컴뱂 인터페이스 구현
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

    FORCEINLINE UUnitCombatComponent* GetUnitCombatComponent() const { return UnitCombatComponent; }
public:
    UFUNCTION(BlueprintCallable, Category = "RVO")
    void SetAttackTarget(AActor* InTargetActor);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void Attack();

    // 풀에서 꺼내질 때: GAS 초기화 + AI 재가동
    virtual void ActivateUnit();

    // 풀로 돌아갈 때: AI 중지 + GAS 정리
    virtual void DeactivateUnit();
protected:
    virtual void PossessedBy(AController* NewController) override;

private:
    void InitUnitStartUpData();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Movement")
    TObjectPtr<AActor> TargetActor = nullptr;
            
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UUnitCombatComponent> UnitCombatComponent;

private:
    // AI 컨트롤러 캐싱
    class AAIController* AIController = nullptr;


};
