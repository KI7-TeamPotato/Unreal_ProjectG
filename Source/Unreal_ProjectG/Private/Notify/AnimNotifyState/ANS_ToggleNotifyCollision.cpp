// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AnimNotifyState/ANS_ToggleNotifyCollision.h"
#include "PGFunctionLibrary.h"
#include "Components/Combat/PawnCombatComponent.h"

//void UANS_ToggleNotifyCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
//{
//    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
//
//    // 현재 월드가 게임 월드인지 확인
//    UWorld* World = MeshComp->GetWorld();
//    if (!World || !World->IsGameWorld())
//    {
//        return;
//    }
//
//    AActor* OwnerActor = MeshComp->GetOwner();
//    UPawnCombatComponent* PawnCombatComp = UPGFunctionLibrary::NativeGetCombatComponentFromActor(OwnerActor);
//    if (PawnCombatComp)
//    {
//        //PawnCombatComp->ToggleWeaponCollision(true);
//        PawnCombatComp->ToggleWeaponTrace(true);
//    }
//}

void UANS_ToggleNotifyCollision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    UWorld* World = MeshComp->GetWorld();
    if (!World || !World->IsGameWorld())
    {
        return;
    }

    AActor* OwnerActor = MeshComp->GetOwner();
    UPawnCombatComponent* PawnCombatComp = UPGFunctionLibrary::NativeGetCombatComponentFromActor(OwnerActor);
    if (PawnCombatComp)
    {
        //PawnCombatComp->ToggleWeaponCollision(false);
        PawnCombatComp->ActivateWeaponTrace(bEnableTraceDebug, TraceDebugDuration);
    }
}

void UANS_ToggleNotifyCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    UWorld* World = MeshComp->GetWorld();
    if (!World || !World->IsGameWorld())
    {
        return;
    }

    AActor* OwnerActor = MeshComp->GetOwner();
    UPawnCombatComponent* PawnCombatComp = UPGFunctionLibrary::NativeGetCombatComponentFromActor(OwnerActor);
    if (PawnCombatComp)
    {
        //PawnCombatComp->ToggleWeaponCollision(false);
        PawnCombatComp->ResetOverlappedActors();
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);
}
