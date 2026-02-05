// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Hero/PGHeroLinkedAnimLayer.h"
#include "AnimInstance/Hero/PGHeroAnimInstance.h"

UPGHeroAnimInstance* UPGHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
    return Cast<UPGHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}