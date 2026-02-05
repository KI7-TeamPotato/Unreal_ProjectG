// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_PROJECTG_API UHeroResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeroResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
    //체력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    float Health = 100.0f;
    //최대체력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    float MaxHealth = 100.0f;

    //공격력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    float AttakcPower = 10.0f;
    
    //공격속도
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    float AttackSpeed = 1.0f;

    //유닛 소환용 코스트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    int32 UsableCost = 0;

    //유닛 소환용 코스트의 최댓값
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
    int32 MaxCost = 100;

private:
    bool bIsAlive = true;
};
