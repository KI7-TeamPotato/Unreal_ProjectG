// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbilityTypes.h"

UPawnCombatComponent::UPawnCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPawnCombatComponent::EquipWeapon(TSubclassOf<APGWeaponBase> NewWeapon)
{
    APGWeaponBase* SpawnedWeapon = nullptr;
    ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
    if (OwningCharacter && AttachmentSocketName != NAME_None)
    {
        SpawnedWeapon = GetWorld()->SpawnActor<APGWeaponBase>(NewWeapon);
        // 무기의 소유자 설정(특히, Instigator와 Owner 설정 필수)
        SpawnedWeapon->SetOwningPawn(OwningCharacter);
        SpawnedWeapon->SetInstigator(OwningCharacter);
        SpawnedWeapon->SetOwner(OwningCharacter);

        if (SpawnedWeapon)
        {
            SpawnedWeapon->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachmentSocketName);
            CurrentEquippedWeapon = SpawnedWeapon;
        }
    }
}