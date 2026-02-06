// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Shared/SharedAbility_SpawnWeapon.h"
#include "Objects/EquipWeaponEventDataObject.h"
#include "Items/Weapons/PGWeaponBase.h"
#include "Components/Combat/PawnCombatComponent.h"

USharedAbility_SpawnWeapon::USharedAbility_SpawnWeapon()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void USharedAbility_SpawnWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 트리거를 통해 전달된 이벤트 데이터에서 무기 클래스가 담긴 오브젝트를 추출
    if (TriggerEventData && TriggerEventData->OptionalObject)
    {
        const UEquipWeaponEventDataObject* EquipWeaponDataObject = Cast<UEquipWeaponEventDataObject>(TriggerEventData->OptionalObject);
        TSubclassOf<APGWeaponBase> InEquipTryHeroWeaponClass = EquipWeaponDataObject->GetEquippedWeaponClass();

        // 1. 무기를 스폰하고 장비
        APGWeaponBase* SpawnedHeroWeapon;
       
        // 스폰 인스티게이터 및 오너 설정 필수
        FActorSpawnParameters SpawnParams;
        SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
        SpawnParams.Owner = GetAvatarActorFromActorInfo();
        SpawnedHeroWeapon = GetWorld()->SpawnActor<APGWeaponBase>(InEquipTryHeroWeaponClass, SpawnParams);

        SpawnedHeroWeapon->AttachToComponent(
            CurrentActorInfo->SkeletalMeshComponent.Get(),
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
            EquipWeaponAttachmentSocketName
        );

        // 폰 Combat 컴포넌트의 무기 장비 상태 업데이트
        GetPawnCombatComponent()->InitializePawnEquippedState(SpawnedHeroWeapon, true);
    }
}
