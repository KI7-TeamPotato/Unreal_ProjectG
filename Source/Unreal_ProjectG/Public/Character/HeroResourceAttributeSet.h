// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Framework/GASMacro.h"
#include "HeroResourceAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UHeroResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UHeroResourceAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData Cost;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, Cost)

    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData MaxCost;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, MaxCost)

    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, AttackPower)

    UPROPERTY(BlueprintReadOnly, Category = "Attribute")
    FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(UHeroResourceAttributeSet, AttackSpeed)


};
