// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_SendGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UAN_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
    public:
    // AnimNotify가 트리거될 때 호출되는 함수
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
    // 전송할 게임플레이 이벤트 태그
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Event")
    FGameplayTag GameplayEventTag;
};
