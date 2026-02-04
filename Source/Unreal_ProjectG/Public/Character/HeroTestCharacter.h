// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HeroCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/EquipmentInterface.h"
#include "HeroTestCharacter.generated.h"

class UPGAbilitySystemComponent;
class UHeroResourceAttributeSet;
class UHeroEquipmentComponent;

/**
 * 어빌리티 테스트용 캐릭터,
 * 후에 삭제 예정
 */
UCLASS()
class UNREAL_PROJECTG_API AHeroTestCharacter : public AHeroCharacter, public IAbilitySystemInterface, public IEquipmentInterface
{
	GENERATED_BODY()

public:
    AHeroTestCharacter();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
    FORCEINLINE UPGAbilitySystemComponent* GetPGAbilitySystemComponent() const { return PGAbilitySystemComponent; }

    virtual UEquipmentComponent* GetEquipmentComponent() const override;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    TObjectPtr<UPGAbilitySystemComponent> PGAbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    TObjectPtr<UHeroResourceAttributeSet> HeroResourceAttributeSet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentSystem")
    TObjectPtr<UHeroEquipmentComponent> HeroEquipmentComponent;
};
