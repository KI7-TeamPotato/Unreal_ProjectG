// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"


class APGHeroWeapon;
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECTG_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
    //virtual void ToggleWeaponCollision(bool bEnableCollision) override;

    virtual void ActivateWeaponTrace(bool bEnableTraceDebug, float InTraceDebugDuration) override;

protected:
    virtual void BeginPlay() override;

    virtual void OnHitTargetActor(AActor* HitActor) override;

protected:
    // 무기 스태틱 메시 캐싱
    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> CachedWeaponStaticMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Weapon")
    FVector WeaponTraceBoxExtent = FVector(5.f, 5.f, 50.f);

};
