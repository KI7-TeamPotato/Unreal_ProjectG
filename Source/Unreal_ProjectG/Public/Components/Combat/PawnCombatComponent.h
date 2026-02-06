// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GamePlayAbilitySpecHandle.h"
#include "PawnCombatComponent.generated.h"

class APGWeaponBase;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECTG_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
    UPawnCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TrySpawnWeaponFromEvent(TSubclassOf<APGWeaponBase> NewWeapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    APGWeaponBase* GetCharacterCurrentEquippedWeapon() const { return CurrentEquippedWeapon.Get(); }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void InitializePawnEquippedState(APGWeaponBase* InEquippedWeapon, bool bIsEquipped);

    // 스킬 어빌리티 핸들 할당
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AssignSillAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InHandle);

    // 기본 공격 어빌리티 핸들 할당
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AssignBaseAttackAbilitySpecHandle(const FGameplayAbilitySpecHandle& InHandle);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    const FGameplayAbilitySpecHandle& GetBaseAttackAbilitySpecHandle() const { return GrantedBaseAttackAbilitySpecHandle; }

public:
    // 나중에 태그나 다른 타입도 고려
    UPROPERTY(BlueprintReadWrite, Category = "Combat|Property")
    bool bWeaponEquipped = false;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Combat|Data")
    TWeakObjectPtr<APGWeaponBase> CurrentEquippedWeapon;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Data")
    FName AttachmentSocketName = NAME_None;

    // 스킬 어빌리티를 위한 어빌리티 스펙 핸들들
    UPROPERTY(VisibleAnywhere, Category = "Combat|Data")
    TArray<FGameplayAbilitySpecHandle> GrantedSkillAbilitySpecHandles;

    // 기본 공격 어빌리티를 위한 어빌리티 스펙 핸들
    UPROPERTY(VisibleAnywhere, Category = "Combat|Data")
    FGameplayAbilitySpecHandle GrantedBaseAttackAbilitySpecHandle;
};
