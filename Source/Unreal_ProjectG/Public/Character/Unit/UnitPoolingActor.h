// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitPoolingActor.generated.h"
class AUnitPoolingActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPoolObjectDespawn, AUnitPoolingActor*, PoolActor);

UCLASS()
class UNREAL_PROJECTG_API AUnitPoolingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitPoolingActor();

    FOnPoolObjectDespawn OnPoolObjectDespawn;

    UFUNCTION(BlueprintCallable, Category = "ObjectPool")
    void DeActivate();

    void SetActive(bool IsActive);
    void SetLifeSpan(float LifeTime);
    void SetPoolIndex(int32 Index);

    bool IsActive() { return Active; }
    int32 GetPoolIndex();

protected:
    bool Active = false;
    float LifeSpan = 0.0f;
    int32 PoolIndex = 0;

    FTimerHandle LifeSpanTimer;
};
