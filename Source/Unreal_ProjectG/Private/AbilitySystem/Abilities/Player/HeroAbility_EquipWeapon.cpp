// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/HeroAbility_EquipWeapon.h"
#include "Objects/EquipWeaponEventDataObject.h"
#include "Items/Weapons/PGHeroWeapon.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AnimInstance/Hero/PGHeroLinkedAnimLayer.h"

UHeroAbility_EquipWeapon::UHeroAbility_EquipWeapon()
{
    // 기본 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UHeroAbility_EquipWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 트리거를 통해 전달된 이벤트 데이터에서 무기 클래스가 담긴 오브젝트를 추출
    if (TriggerEventData && TriggerEventData->OptionalObject)
    {
        const UEquipWeaponEventDataObject* EquipWeaponDataObject = Cast<UEquipWeaponEventDataObject>(TriggerEventData->OptionalObject);
      
        // 1. 무기를 스폰하고 장비
        APGWeaponBase* SpawnedHeroWeapon;
        SpawnAndEquipWeapon(EquipWeaponDataObject->GetEquippedWeaponClass(), SpawnedHeroWeapon);

        // 2. 애니메이션 레이어 설정
        if (SpawnedHeroWeapon)
        {
            LinkedAnimLayerSetup(SpawnedHeroWeapon);
        }
    }
}

void UHeroAbility_EquipWeapon::SpawnAndEquipWeapon(TSubclassOf<APGWeaponBase> InEquipTryHeroWeaponClass, APGWeaponBase*& OutEquippedHeroWeapon)
{
    // 스폰 인스티게이터 및 오너 설정 필수
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
    SpawnParams.Owner = GetAvatarActorFromActorInfo();
    OutEquippedHeroWeapon = GetWorld()->SpawnActor<APGWeaponBase>(InEquipTryHeroWeaponClass, SpawnParams);

    OutEquippedHeroWeapon->AttachToComponent(
        CurrentActorInfo->SkeletalMeshComponent.Get(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale,
        EquipWeaponAttachmentSocketName
        );

    // 폰 Combat 컴포넌트의 무기 장비 상태 업데이트
    GetPawnCombatComponent()->SetWeaponEquipped(OutEquippedHeroWeapon, true);
}

void UHeroAbility_EquipWeapon::LinkedAnimLayerSetup(APGWeaponBase* InEquippedHeroWeapon)
{
    // 이 어빌리티를 실행한 액터에 무기의 애니메이션 레이어를 연결
    APGHeroWeapon* HeroWeapon = Cast<APGHeroWeapon>(InEquippedHeroWeapon);

    if (HeroWeapon)
    {
        USkeletalMeshComponent* SkeletalMeshComp = CurrentActorInfo->SkeletalMeshComponent.Get();
        SkeletalMeshComp->LinkAnimClassLayers(HeroWeapon->GetHeroWeaponData().WeaponAnimLayer);
    }
}
