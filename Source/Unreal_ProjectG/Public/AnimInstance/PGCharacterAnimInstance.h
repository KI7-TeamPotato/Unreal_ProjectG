// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PGBaseAnimInstance.h"
#include "PGCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 *   유닛과 캐릭터가 공통으로 사용할 변수를 여기서 정의
 */
UCLASS()
class UNREAL_PROJECTG_API UPGCharacterAnimInstance : public UPGBaseAnimInstance
{
	GENERATED_BODY()
	
public:
    virtual void NativeInitializeAnimation() override;

    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
    // TODO : 캐릭터 타입을 우리의 캐릭터 타입으로 변경 변경
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwningCharacter;

    UPROPERTY()
    TObjectPtr<UCharacterMovementComponent> OwningCharacterMovement;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    float GroundSpeed;
};
