// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/PGStructTypes.h"
#include "AbilitySystem/Abilities/PGHeroGameplayAbility.h"

bool FPGHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}
