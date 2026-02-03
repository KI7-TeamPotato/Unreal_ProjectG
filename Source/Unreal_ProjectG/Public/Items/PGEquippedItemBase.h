// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGEquippedItemBase.generated.h"

UCLASS()
class UNREAL_PROJECTG_API APGEquippedItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APGEquippedItemBase();

    void SetOwningPawn(APawn* NewOwningPawn);
    APawn* GetOwningPawn() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "EquippedItem")
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY()
    TWeakObjectPtr<APawn> OwningPawn;
};
