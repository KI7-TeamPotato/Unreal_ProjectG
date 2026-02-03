// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AnimNotifyState/ANS_ToggleNotifyCollision.h"
#include "PGFunctionLibrary.h"
#include "Components/Equipment/EquipmentComponent.h"
#include "Items/Weapons/PGWeaponBase.h"

void UANS_ToggleNotifyCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    APGWeaponBase* ToggleWeapon = UPGFunctionLibrary::NativeGetEquipComponentFromActor(MeshComp->GetOwner())->GetCharacterCurrentEquippedWeapon();
    if (ToggleWeapon)
    {
        ToggleWeapon->ToggleWeaponCollision(true);
    }
}

void UANS_ToggleNotifyCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    APGWeaponBase* ToggleWeapon = UPGFunctionLibrary::NativeGetEquipComponentFromActor(MeshComp->GetOwner())->GetCharacterCurrentEquippedWeapon();
    if (ToggleWeapon)
    {
        ToggleWeapon->ToggleWeaponCollision(false);
    }
}