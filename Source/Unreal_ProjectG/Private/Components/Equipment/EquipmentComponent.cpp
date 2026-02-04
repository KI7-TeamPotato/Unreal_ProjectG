// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Equipment/EquipmentComponent.h"
#include "Items/Weapons/PGWeaponBase.h"

void UEquipmentComponent::SetCurrentEquippedWeapon(APGWeaponBase* NewWeapon)
{
    CurrentEquippedWeapon = NewWeapon;
}
