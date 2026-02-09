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
    virtual void ToggleWeaponCollision(bool bEnableCollision) override;

protected:
    virtual void BeginPlay() override;

    virtual void OnHitTargetActor(AActor* HitActor) override;

    UFUNCTION()
    void OnWeaponBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

protected:
    // 무기 스태틱 메시 캐싱
    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> CachedWeaponStaticMesh;
};
