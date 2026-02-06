// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PGCharacterBase.h"
#include "UnitCharacter.generated.h"

class UUnitCombatComponent;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API AUnitCharacter : public APGCharacterBase
{
	GENERATED_BODY()
	
public:
    AUnitCharacter();

    // 컴뱂 인터페이스 구현
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

    FORCEINLINE UUnitCombatComponent* GetUnitCombatComponent() const { return UnitCombatComponent; }

protected:
    virtual void BeginPlay() override;

    virtual void PossessedBy(AController* NewController) override;

private:
    void InitUnitStartUpData();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UUnitCombatComponent> UnitCombatComponent;
};
