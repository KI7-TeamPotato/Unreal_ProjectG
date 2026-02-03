// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PGBaseAnimInstance.h"
#include "PGFunctionLibrary.h"

bool UPGBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return UPGFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
    }

    return false;
}
