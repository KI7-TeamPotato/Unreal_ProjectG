// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayEffectTypes.h"
#include "ScalableFloat.h"
#include "DataAsset_ArmorData.generated.h"

class UGameplayEffect;
class UPGAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UDataAsset_ArmorData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Armor|Data")
    void MakeOutgoingArmorEffectSpecHandle(UPGAbilitySystemComponent* InASC, int32 InLevel = 1) const;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Armor|Data")
    TSoftClassPtr<UGameplayEffect> ArmorGameplayEffectClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Armor|Data")
    TMap<FGameplayTag, FScalableFloat> AttributeModifiers;
};
