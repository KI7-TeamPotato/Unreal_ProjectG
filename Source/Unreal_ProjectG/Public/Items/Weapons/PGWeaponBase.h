// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PGEquippedItemBase.h"
#include "PGWeaponBase.generated.h"

class UBoxComponent;

//DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*);

UCLASS()
class UNREAL_PROJECTG_API APGWeaponBase : public APGEquippedItemBase
{
	GENERATED_BODY()
	
public:	
	APGWeaponBase();

    // 무기 충돌 박스 활성화/비활성화 함수, 애니메이션 노티파이에서 호출 예정
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void ToggleWeaponCollision(bool bShouldEnable);

    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

    // 기능이 많아져서 따로 컴포넌트를 만든다면 다시 추가
    //FOnTargetInteractedDelegate OnWeaponHitTarget;
    //FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
    // 충돌 박스 오버랩 이벤트 핸들러
    UFUNCTION()
    virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // 적과 충돌 했을 때 처리하는 함수
    UFUNCTION()
    virtual void WeaponHitTargetHandler(AActor* HitActor);

    // 적과의 충돌이 끝났을 때 처리하는 함수
    UFUNCTION()
    virtual void WeaponPulledFromTargetHandler(AActor* HitActor);
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    TObjectPtr<UBoxComponent> WeaponCollisionBox;

    TArray<AActor*> OverlappedActors;
};
