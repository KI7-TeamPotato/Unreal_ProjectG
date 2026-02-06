// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PGWeaponBase.h"
#include "Components/BoxComponent.h"

APGWeaponBase::APGWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
    WeaponCollisionBox->SetupAttachment(GetRootComponent());
    WeaponCollisionBox->SetBoxExtent(FVector(20.f));
    WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APGWeaponBase::OnCollisionBoxBeginOverlap);
    WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APGWeaponBase::OnCollisionBoxEndOverlap);
}

void APGWeaponBase::ToggleWeaponCollision(bool bShouldEnable)
{
    if (bShouldEnable)
    {
        WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        OverlappedActors.Empty();
    }
}

void APGWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APawn* WeaponOwningPawn = GetInstigator();

    checkf(WeaponOwningPawn, TEXT("Forgot to assign an Instigator for the weapon %s?"), *GetName());
    
    if (APawn* HitPawn = Cast<APawn>(OtherActor))
    {
        // TODO: 아군인지 적군인지 확인하는 로직 추가 필요
        if (OtherActor != WeaponOwningPawn)
        {
            // 다향성 위해 가상 함수로 분리
            WeaponHitTargetHandler(OtherActor);

        }
        // 상대방의 히트 리액션 재생 등은 여기서 처리
        //OnWeaponHitTarget.ExecuteIfBound(OtherActor);
    }
}

void APGWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    APawn* WeaponOwningPawn = GetInstigator();

    checkf(WeaponOwningPawn, TEXT("Forgot to assign an Instigator for the weapon %s?"), *GetName());

    if (APawn* HitPawn = Cast<APawn>(OtherActor))
    {
        // TODO: 아군인지 적군인지 확인하는 로직 추가 필요
        WeaponPulledFromTargetHandler(OtherActor);
        
        //OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
    }
}

void APGWeaponBase::WeaponHitTargetHandler(AActor* HitActor)
{

}

void APGWeaponBase::WeaponPulledFromTargetHandler(AActor* HitActor)
{

}
