// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AnimNotify/AN_SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    // 현재 월드가 게임 월드인지 확인
    UWorld* World = MeshComp->GetWorld();
    if (!World || !World->IsGameWorld())
    {
        return;
    }

    AActor* OwnerActor = MeshComp->GetOwner();
    if (OwnerActor)
    {
        // 게임플레이 이벤트 전송
        FGameplayEventData EventData;
        EventData.Instigator = OwnerActor;
        EventData.Target = OwnerActor;

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, GameplayEventTag, EventData);
    }
}
