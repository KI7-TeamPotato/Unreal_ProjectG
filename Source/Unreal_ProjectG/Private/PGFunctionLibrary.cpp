// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Interfaces/EquipmentInterface.h"
#include "Components/Equipment/EquipmentComponent.h"

UPGAbilitySystemComponent* UPGFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
    check(InActor);

    return CastChecked<UPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UPGFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UPGAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

UEquipmentComponent* UPGFunctionLibrary::NativeGetEquipComponentFromActor(AActor* InActor)
{
    check(InActor);

    if(IEquipmentInterface* EquipmentInterface = Cast<IEquipmentInterface>(InActor))
    {
        return EquipmentInterface->GetEquipmentComponent();
    }

    if (UEquipmentComponent* EquipComp = InActor->FindComponentByClass<UEquipmentComponent>())
    {
        return EquipComp;
    }

    return nullptr;
}

UEquipmentComponent* UPGFunctionLibrary::BP_GetEquipComponentFromActor(AActor* InActor, EPGValidType& OutValidType)
{
    UEquipmentComponent* EquipComp = NativeGetEquipComponentFromActor(InActor);

    OutValidType = EquipComp ? EPGValidType::Valid : EPGValidType::InValid;
    return EquipComp;
}
