// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/PGHeroWeapon.h"

APGHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<APGHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}
