// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/PGCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UPGCharacterAttributeSet::UPGCharacterAttributeSet()
{
    InitMaxHealth(100.0f);
    InitHealth(100.0f);
    InitCost(0.0f);
    InitCost(100.0f);
    InitAttackPower(10.0f);
    InitAttackSpeed(1.0f);
}

void UPGCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
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

void UPGCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        const float NewCurrentHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());

        SetHealth(NewCurrentHealth);

        if (FMath::IsNearlyZero(GetHealth()))
        {
            UE_LOG(LogTemp, Log, TEXT("Dead"));
        }
    }
}