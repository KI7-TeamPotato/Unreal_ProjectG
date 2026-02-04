// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Equipment/HeroEquipmentComponent.h"
#include "Items/Weapons/PGHeroWeapon.h"

APGHeroWeapon* UHeroEquipmentComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<APGHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}
