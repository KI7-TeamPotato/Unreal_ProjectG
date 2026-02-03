// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/HeroResourceAttributeSet.h"
#include "GameplayEffectExtension.h"

UHeroResourceAttributeSet::UHeroResourceAttributeSet()
{
    InitMaxHealth(100.0f);
    InitHealth(100.0f);
    InitCost(0.0f);
    InitCost(100.0f);
    InitAttackPower(10.0f);
    InitAttackSpeed(1.0f);
}

void UHeroResourceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    if (Attribute == GetCostAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxCost());
    }
}

void UHeroResourceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        if (FMath::IsNearlyZero(GetHealth()))
        {
            UE_LOG(LogTemp, Log, TEXT("Dead"));
        }
    }
}