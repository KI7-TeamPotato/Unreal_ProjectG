// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "PGStructTypes.generated.h"

class UPGHeroGameplayAbility;
class UPGHeroLinkedAnimLayer;
/**
 * 
 */

// 어빌리티 세트 구조체
USTRUCT(BlueprintType)
struct FPGHeroAbilitySet
{
    GENERATED_BODY()

public:
    // 공통으로 들어갈 어빌리티 ID (기본 공격, 스킬 1, 스킬 2 등)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    // 영웅에서 부여될 어빌리티
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UPGHeroGameplayAbility> AbilityToGrant;

    // 유효성 검사 함수
    bool IsValid() const;
};

// 무기 데이터 구조체
USTRUCT(BlueprintType)
struct FPGHeroWeaponData
{
    GENERATED_BODY()

    // 무기 스태틱 메시
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftObjectPtr<UStaticMesh> SoftWeaponMesh;

    // 무기 애니메이션 레이어
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UPGHeroLinkedAnimLayer> WeaponAnimLayer;    
    
    // 무기 기본 경격 어빌리티
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    FPGHeroAbilitySet BaseAttackAbility;

    // 무기 스킬 어빌리티들
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FPGHeroAbilitySet> WeaponSkillAbilities;

    // 무기 아이콘 텍스처
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};