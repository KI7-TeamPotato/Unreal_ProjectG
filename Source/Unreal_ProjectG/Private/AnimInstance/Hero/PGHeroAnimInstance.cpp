// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Hero/PGHeroAnimInstance.h"
#include "Character/HeroTestCharacter.h"

void UPGHeroAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (OwningCharacter.IsValid())
    {
        OwningHeroCharacter = Cast<AHeroTestCharacter>(OwningCharacter.Get());
    }
}
