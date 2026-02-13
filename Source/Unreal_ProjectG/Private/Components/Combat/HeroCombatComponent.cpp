// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Character/Hero/HeroCharacter.h"

void UHeroCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    AHeroCharacter* HeroOwner = Cast<AHeroCharacter>(GetOwner());
    if (HeroOwner)
    {
        CachedWeaponMeshComponent = HeroOwner->GetWeaponStaticMesh();
    }
}