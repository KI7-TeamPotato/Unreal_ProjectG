// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AnimNotifyState/ANS_ToggleNotifyCollision.h"
#include "PGFunctionLibrary.h"
#include "Components/Equipment/EquipmentComponent.h"
#include "Items/Weapons/PGWeaponBase.h"

void UANS_ToggleNotifyCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    // 현재 월드가 게임 월드인지 확인
    UWorld* World = MeshComp->GetWorld();
    if (!World || !World->IsGameWorld())
    {
        return;
    }

    AActor* OwnerActor = MeshComp->GetOwner();

    if (APGWeaponBase* ToggleWeapon = UPGFunctionLibrary::NativeGetEquipComponentFromActor(OwnerActor)->GetCharacterCurrentEquippedWeapon())
    {
        ToggleWeapon->ToggleWeaponCollision(true);
    }
}

void UANS_ToggleNotifyCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    UWorld* World = MeshComp->GetWorld();
    if (!World || !World->IsGameWorld())
    {
        return;
    }

    AActor* OwnerActor = MeshComp->GetOwner();

    if (APGWeaponBase* ToggleWeapon = UPGFunctionLibrary::NativeGetEquipComponentFromActor(OwnerActor)->GetCharacterCurrentEquippedWeapon())
    {
        ToggleWeapon->ToggleWeaponCollision(false);
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);
}
