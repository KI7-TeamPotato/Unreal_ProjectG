// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BaseStructure.h"

// Sets default values
ABaseStructure::ABaseStructure()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseStructure::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

