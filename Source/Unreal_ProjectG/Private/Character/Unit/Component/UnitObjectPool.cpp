// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/Component/UnitObjectPool.h"
#include "Character/Unit/UnitPoolingActor.h"

// Sets default values for this component's properties
UUnitObjectPool::UUnitObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AUnitPoolingActor* UUnitObjectPool::SpawnPooledObject()
{
    for (AUnitPoolingActor* PoolAbleActor : ObjectPool)
    {
        if (PoolAbleActor && !PoolAbleActor->IsActive())
        {
            PoolAbleActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
            PoolAbleActor->SetLifeSpan(PooledObjectLifeSpan);
            PoolAbleActor->SetActive(true);
            SpawnPoolIndex.Add(PoolAbleActor->GetPoolIndex());

            return PoolAbleActor;
        }
    }

    if (SpawnPoolIndex.Num() > 0)
    {
        int32 PooledObjectIndex = SpawnPoolIndex[0];
        SpawnPoolIndex.Remove(PooledObjectIndex);
        AUnitPoolingActor* PoolAbleActor = ObjectPool[PooledObjectIndex];

        if (PoolAbleActor)
        {
            PoolAbleActor->SetActive(false);

            PoolAbleActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
            PoolAbleActor->SetLifeSpan(PooledObjectLifeSpan);
            PoolAbleActor->SetActive(true);
            SpawnPoolIndex.Add(PoolAbleActor->GetPoolIndex());

            return PoolAbleActor;
        }
    }

    return nullptr;
}


// Called when the game starts
void UUnitObjectPool::BeginPlay()
{
	Super::BeginPlay();

    if (PoolObjectSubclass.Get())
    {
        UWorld* const World = GetWorld();

        if (World)
        {
            for (size_t i = 0; i < PoolSize; i++)
            {
                AUnitPoolingActor* PoolAbleActor = World->SpawnActor<AUnitPoolingActor>
                    (
                        PoolObjectSubclass,
                        FVector().ZeroVector,
                        FRotator().ZeroRotator
                    );

                if (PoolAbleActor)
                {
                    PoolAbleActor->SetActive(false);
                    PoolAbleActor->SetPoolIndex(i);
                    PoolAbleActor->OnPoolObjectDespawn.AddDynamic(this, &UUnitObjectPool::OnPoolObjectDespawn);
                }
            }
        }
    }
}

void UUnitObjectPool::OnPoolObjectDespawn(AUnitPoolingActor* PoolActor)
{
    SpawnPoolIndex.Remove(PoolActor->GetPoolIndex());
}


