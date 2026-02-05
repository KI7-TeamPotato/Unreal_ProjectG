// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
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
    void TryEquippedWeaponFromEvent(TSubclassOf<APGWeaponBase> NewWeapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    APGWeaponBase* GetCharacterCurrentEquippedWeapon() const { return CurrentEquippedWeapon.Get(); }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetWeaponEquipped(APGWeaponBase* InEquippedWeapon, bool bIsEquipped);

public:
    // 나중에 태그나 다른 타입도 고려
    UPROPERTY(BlueprintReadWrite, Category = "Combat|Property")
    bool bWeaponEquipped = false;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Combat|Data")
    TWeakObjectPtr<APGWeaponBase> CurrentEquippedWeapon;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Data")
    FName AttachmentSocketName = NAME_None;
};
