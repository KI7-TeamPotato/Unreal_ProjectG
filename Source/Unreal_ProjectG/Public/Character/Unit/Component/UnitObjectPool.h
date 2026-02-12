// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitObjectPool.generated.h"
class AUnitPoolingActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_PROJECTG_API UUnitObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitObjectPool();

    UFUNCTION(BlueprintCallable, Category = "ObjectPool")
    AUnitPoolingActor* SpawnPooledObject();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "ObjectPool")
    void OnPoolObjectDespawn(AUnitPoolingActor* PoolActor);
protected:
    UPROPERTY(EditAnywhere, Category = "ObjectPool")
    TSubclassOf<AUnitPoolingActor> PoolObjectSubclass = nullptr;

    UPROPERTY(EditAnywhere, Category = "ObjectPool")
    int32 PoolSize = 20;

    UPROPERTY(EditAnywhere, Category = "ObjectPool")
    float PooledObjectLifeSpan = 0.0f;

protected:
    TArray<AUnitPoolingActor*> ObjectPool;
    TArray<int32> SpawnPoolIndex;
};
