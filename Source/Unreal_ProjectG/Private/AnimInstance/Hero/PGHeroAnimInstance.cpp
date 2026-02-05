// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Hero/PGHeroAnimInstance.h"
#include "Character/Hero/HeroCharacter.h"

void UPGHeroAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (OwningCharacter.IsValid())
    {
        OwningHeroCharacter = Cast<AHeroCharacter>(OwningCharacter.Get());
    }
}
