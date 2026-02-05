// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PGCharacterAnimInstance.h"
#include "PGHeroAnimInstance.generated.h"

// TODO : 나중에 우리의 캐릭터로 변경
class AHeroTestCharacter;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPGHeroAnimInstance : public UPGCharacterAnimInstance
{
	GENERATED_BODY()
	
public: 
    virtual void NativeInitializeAnimation() override;

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
    TWeakObjectPtr<AHeroTestCharacter> OwningHeroCharacter;
};
