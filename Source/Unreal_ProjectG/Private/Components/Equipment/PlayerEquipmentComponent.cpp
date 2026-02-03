// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Equipment/PlayerEquipmentComponent.h"
#include "Items/Weapons/PGPlayerWeapon.h"

APGPlayerWeapon* UPlayerEquipmentComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<APGPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}
