// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitPoolingActor.h"

// Sets default values
AUnitPoolingActor::AUnitPoolingActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitPoolingActor::SetActive(bool IsActive)
{
    Active = IsActive;
    SetActorHiddenInGame(IsActive);
    GetWorldTimerManager().SetTimer(
        LifeSpanTimer,
        this, 
        &AUnitPoolingActor::DeActivate,
        LifeSpan,
        false
        );
}

void AUnitPoolingActor::DeActivate()
{
    SetActive(false);
    GetWorldTimerManager().ClearAllTimersForObject(this);
    OnPoolObjectDespawn.Broadcast(this);
}

void AUnitPoolingActor::SetLifeSpan(float LifeTime)
{
    LifeSpan = LifeTime;
}

void AUnitPoolingActor::SetPoolIndex(int32 Index)
{
    PoolIndex = Index;
}

int32 AUnitPoolingActor::GetPoolIndex()
{
    return int32();
}


