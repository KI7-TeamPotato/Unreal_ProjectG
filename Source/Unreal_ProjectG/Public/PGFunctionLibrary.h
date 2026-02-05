// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Types/PGEnumTypes.h"
#include "PGFunctionLibrary.generated.h"

class UPGAbilitySystemComponent;
class UPawnCombatComponent;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    static UPGAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

    // 타겟 액터가 특정 태그를 가지고 있는지 확인하는 네이티브 함수
    static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

    //UFUNCTION(BlueprintCallable, Category = "ProjectG|FunctionLibrary")
    //static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, )

    static UPawnCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, Category = "ProjectG|FunctionLibrary", meta = (DisplayName = "Get Current Weapon From Actor", ExpandEnumAsExecs = "OutValidType"))
    static UPawnCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, EPGValidType& OutValidType);

};
