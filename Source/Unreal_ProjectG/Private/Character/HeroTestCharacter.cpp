// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroTestCharacter.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Character/HeroResourceAttributeSet.h"
#include "Components/Equipment/HeroEquipmentComponent.h"

AHeroTestCharacter::AHeroTestCharacter()
{
    PGAbilitySystemComponent = CreateDefaultSubobject<UPGAbilitySystemComponent>(TEXT("PGAbilitySystemComponent"));
    HeroResourceAttributeSet = CreateDefaultSubobject<UHeroResourceAttributeSet>(TEXT("HeroResourceAttributeSet"));
    HeroEquipmentComponent = CreateDefaultSubobject<UHeroEquipmentComponent>(TEXT("HeroEquipmentComponent"));
}

UAbilitySystemComponent* AHeroTestCharacter::GetAbilitySystemComponent() const
{
    return GetPGAbilitySystemComponent();
}

UEquipmentComponent* AHeroTestCharacter::GetEquipmentComponent() const
{
    return HeroEquipmentComponent;
}

void AHeroTestCharacter::BeginPlay()
{

}
