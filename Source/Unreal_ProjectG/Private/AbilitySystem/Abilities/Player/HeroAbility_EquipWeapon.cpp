// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/HeroAbility_EquipWeapon.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Items/Weapons/PGHeroWeapon.h"
#include "AnimInstance/Hero/PGHeroLinkedAnimLayer.h"
#include "Components/Combat/HeroCombatComponent.h"

UHeroAbility_EquipWeapon::UHeroAbility_EquipWeapon()
{
    // 기본 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UHeroAbility_EquipWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    CachedEquippedWeapon = GetHeroCombatComponentFromActorInfo()->GetHeroCurrentEquippedWeapon();

    if (CachedEquippedWeapon)
    {
        // 2. 애니메이션 레이어 설정
        LinkedAnimLayerSetup();

        // 3. 무기 어빌리티 부여
        GrantWeaponAbilitiesToHero();
    }
}

void UHeroAbility_EquipWeapon::LinkedAnimLayerSetup()
{
    // 이 어빌리티를 실행한 액터에 무기의 애니메이션 레이어를 연결
    APGHeroWeapon* HeroWeapon = Cast<APGHeroWeapon>(CachedEquippedWeapon);

    if (HeroWeapon)
    {
        USkeletalMeshComponent* SkeletalMeshComp = CurrentActorInfo->SkeletalMeshComponent.Get();
        SkeletalMeshComp->LinkAnimClassLayers(HeroWeapon->GetHeroWeaponData().WeaponAnimLayer);
    }
}

void UHeroAbility_EquipWeapon::GrantWeaponAbilitiesToHero()
{
    UPGAbilitySystemComponent* ASC = GetPGAbilitySystemComponentFromActorInfo();

    FGameplayAbilitySpecHandle BasicAttackAbilitySpecHandle;
    TArray<FGameplayAbilitySpecHandle> SkillAbilitySpecHandles;

    // 기본 공격 어빌리티를 영웅에게 부여하고 핸들 저장
    ASC->GrantHeroWeaponBasicAttackAbility(
        CachedEquippedWeapon->GetHeroWeaponData().BaseAttackAbility,
        GetAbilityLevel(),
        BasicAttackAbilitySpecHandle
    );

    // 무기의 어빌리티들을 영웅에게 부여
    ASC->GrantHeroWeaponSkillAbilities(
        CachedEquippedWeapon->GetHeroWeaponData().WeaponSkillAbilities,
        GetAbilityLevel(),
        SkillAbilitySpecHandles
    );

    // 부여한 어빌리티 핸들을 컴뱃 컴포넌트에 할당
    UHeroCombatComponent* HeroCombatComp = GetHeroCombatComponentFromActorInfo();
    HeroCombatComp->AssignBaseAttackAbilitySpecHandle(BasicAttackAbilitySpecHandle);
    HeroCombatComp->AssignSillAbilitySpecHandle(SkillAbilitySpecHandles);
}
