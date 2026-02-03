// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PGEquippedItemBase.h"

APGEquippedItemBase::APGEquippedItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

void APGEquippedItemBase::SetOwningPawn(APawn* NewOwningPawn)
{
    OwningPawn = NewOwningPawn;
}
    
APawn* APGEquippedItemBase::GetOwningPawn() const
{
    check(OwningPawn.IsValid());

    return OwningPawn.Get();
}

