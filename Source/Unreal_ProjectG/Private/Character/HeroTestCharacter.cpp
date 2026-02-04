// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroTestCharacter.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Character/HeroResourceAttributeSet.h"
#include "Components/Combat/HeroCombatComponent.h"

AHeroTestCharacter::AHeroTestCharacter()
{
    PGAbilitySystemComponent = CreateDefaultSubobject<UPGAbilitySystemComponent>(TEXT("PGAbilitySystemComponent"));
    HeroResourceAttributeSet = CreateDefaultSubobject<UHeroResourceAttributeSet>(TEXT("HeroResourceAttributeSet"));
    HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

UAbilitySystemComponent* AHeroTestCharacter::GetAbilitySystemComponent() const
{
    return GetPGAbilitySystemComponent();
}

UPawnCombatComponent* AHeroTestCharacter::GetPawnCombatComponent() const
{
    return HeroCombatComponent;
}

void AHeroTestCharacter::BeginPlay()
{
    Super::BeginPlay();
}
