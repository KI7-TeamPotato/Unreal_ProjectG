// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Character/PGCharacterBase.h"

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

UPawnCombatComponent* UPGFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
    check(InActor);

    if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->GetPawnCombatComponent();
    }

    if (UPawnCombatComponent* PawnCombatComp = InActor->FindComponentByClass<UPawnCombatComponent>())
    {
        return PawnCombatComp;
    }

    return nullptr;
}

UPawnCombatComponent* UPGFunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, EPGValidType& OutValidType)
{
    UPawnCombatComponent* EquipComp = NativeGetCombatComponentFromActor(InActor);

    OutValidType = EquipComp ? EPGValidType::Valid : EPGValidType::InValid;
    return EquipComp;
}

bool UPGFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UPGAbilitySystemComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);
    UPGAbilitySystemComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);

    FActiveGameplayEffectHandle ActivateGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

    return ActivateGameplayEffectHandle.WasSuccessfullyApplied();
}

bool UPGFunctionLibrary::IsTargetCharacterIsHostile(AActor* InInstigator, AActor* InTargetActor)
{
    // 일단은 두 태그가 다르면 적대 관계로 간주
    APGCharacterBase* InstigatorCharacter = Cast<APGCharacterBase>(InInstigator);
    APGCharacterBase* TargetCharacter = Cast<APGCharacterBase>(InTargetActor);

    if(!InstigatorCharacter || !TargetCharacter)
    {
        return false;
    }

    return InstigatorCharacter->GetTeamTag() != TargetCharacter->GetTeamTag();
}
