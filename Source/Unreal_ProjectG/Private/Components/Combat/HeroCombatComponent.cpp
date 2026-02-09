// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Character/Hero/HeroCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PGGameplayTags.h"

void UHeroCombatComponent::BeginPlay()
{
    Super::BeginPlay();

       // 무기 스태틱 메시 캐싱
    AHeroCharacter* Hero = Cast<AHeroCharacter>(GetOwner());
    if (Hero)
    {
        CachedWeaponStaticMesh = Hero->GetWeaponStaticMesh();

        if (CachedWeaponStaticMesh)
        {
            CachedWeaponStaticMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &UHeroCombatComponent::OnWeaponBeginOverlap);
        }
    }
}

void UHeroCombatComponent::ToggleWeaponCollision(bool bEnableCollision)
{
    if (!CachedWeaponStaticMesh) return;

    if (bEnableCollision)
    {
        CachedWeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
    else
    {
        // 콜리전 비활성화 로직
        CachedWeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        OverlappedActors.Empty();
    }
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }
    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    // 게임 플레이 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        PGGameplayTags::Shared_Event_MeleeHit,
        Data
    );
}

void UHeroCombatComponent::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        OnHitTargetActor(OtherActor);
    }
}
