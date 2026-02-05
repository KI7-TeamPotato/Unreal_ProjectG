// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Character/HeroResourceComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MovementComponent = GetCharacterMovement();

    //화면이 회전하지 않도록 고정
    MovementComponent->bUseControllerDesiredRotation = true;
    MovementComponent->bOrientRotationToMovement = false;
    bUseControllerRotationYaw = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArm);

    ResourceManager = CreateDefaultSubobject<UHeroResourceComponent>(TEXT("ResourceManager"));
}

void AHeroCharacter::SpawnCharacter()
{
    USkeletalMeshComponent* MeshComp = GetMesh();
    MeshComp->bPauseAnims = false;
    MeshComp->SetSimulatePhysics(false);
    MeshComp->SetCollisionProfileName(TEXT("CharacterMesh"));

    MeshComp->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    MeshComp->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
    MeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCharacterMovement()->SetComponentTickEnabled(true);
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    GetCharacterMovement()->Activate();
}

void AHeroCharacter::OnDie()
{
    GetCharacterMovement()->DisableMovement();
    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->SetComponentTickEnabled(false);

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    USkeletalMeshComponent* MeshComp = GetMesh();
    MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
    MeshComp->bPauseAnims = true;
    MeshComp->SetSimulatePhysics(true);

    //MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

    if (OnPlayerDied.IsBound())
    {
        OnPlayerDied.Broadcast();
    }
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

    //ABP 가져오기
    AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (enhancedInputComponent)
    {
        enhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AHeroCharacter::OnMovementInput);
        enhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AHeroCharacter::OnAttackInput);
    }
}

void AHeroCharacter::OnMovementInput(const FInputActionValue& InValue)
{
    if (Controller)
    {
        FVector2D InputDirection = InValue.Get<FVector2D>();
        FVector MoveDirection = FVector(InputDirection.X, InputDirection.Y, 0.0f);
        UE_LOG(LogTemp, Log, TEXT("%.1f, %.1f, %.1f"), MoveDirection.X, MoveDirection.Y, MoveDirection.Z);
        AddMovementInput(MoveDirection);
    }
    else
        UE_LOG(LogTemp, Log, TEXT("Controller Unavailable"));
}

void AHeroCharacter::OnAttackInput()
{

}

