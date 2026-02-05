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

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void EquipWeapon(TSubclassOf<APGWeaponBase> NewWeapon);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    APGWeaponBase* GetCharacterCurrentEquippedWeapon() const { return CurrentEquippedWeapon.Get(); }

protected:
    UPROPERTY(VisibleAnywhere, Category = "Equipment|Data")
    TWeakObjectPtr<APGWeaponBase> CurrentEquippedWeapon;

    UPROPERTY(EditDefaultsOnly, Category = "Equipment|Data")
    FName AttachmentSocketName = NAME_None;
};
