// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGGameplayAbility.h"
#include "PGPlayerGameplayAbility.generated.h"

class UPlayerEquipmentComponent;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPGPlayerGameplayAbility : public UPGGameplayAbility
{
	GENERATED_BODY()
	
public:
    // TODO : 클래스를 우리의 플레이어 캐릭터 타입으로 변경
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    ACharacter* GetPlayerCharacterFromActorInfo();

    // TODO : 클래스를 우리의 플레이어 컨트로러 타입으로 변경
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    APlayerController* GetPlayerControllerFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    UPlayerEquipmentComponent* GetPlayerEquipmentComponentFromActorInfo() const;

    // TODO : 공격의 속성이나 다른 효과가 추가된다면 매개변수를 확장
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float SkillMultiflier);

private:
    TWeakObjectPtr<ACharacter> CachedPlayerCharacter;
    TWeakObjectPtr<APlayerController> CachedPlayerController;
};
