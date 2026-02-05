// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

void AHeroController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AHeroController::BeginPlay()
{
    Super::BeginPlay();
}

void AHeroController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void AHeroController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    if (Subsystem)
    {
        UE_LOG(LogTemp, Log, TEXT("Player Controller Subsystem Available"));
        Subsystem->AddMappingContext(InputMappingContext, 1);
    }
}
