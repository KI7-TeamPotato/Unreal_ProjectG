// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PGStructTypes.generated.h"

class UPGHeroGameplayAbility;
/**
 * 
 */

// 무기 데이터 구조체
USTRUCT(BlueprintType)
struct FPGHeroWeaponData
{
    GENERATED_BODY()

    // 무기 기본 경격 어빌리티
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UPGHeroGameplayAbility> DefaultAttackAbility;

    // 무기 스킬 어빌리티들
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<TSubclassOf<UPGHeroGameplayAbility>> WeaponSkillAbilities;

    // 무기 아이콘 텍스처
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};