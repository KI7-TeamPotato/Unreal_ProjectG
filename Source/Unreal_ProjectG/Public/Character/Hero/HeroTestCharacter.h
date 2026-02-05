// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Hero/HeroCharacter.h"
#include "HeroTestCharacter.generated.h"

/**
 * 어빌리티 테스트용 캐릭터,
 * 후에 삭제 예정
 */
UCLASS()
class UNREAL_PROJECTG_API AHeroTestCharacter : public AHeroCharacter
{
	GENERATED_BODY()

public:
    AHeroTestCharacter();
};
