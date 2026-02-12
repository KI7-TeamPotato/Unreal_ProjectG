
#include "Pawn/BaseStructure.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"
#include "AbilitySystem/PGCharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayEffectTypes.h"


ABaseStructure::ABaseStructure()
{
    PrimaryActorTick.bCanEverTick = false;

    // 1. 캡슐 컴포넌트 설정 (루트)
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    SetRootComponent(CapsuleComp);
    CapsuleComp->SetCollisionProfileName(TEXT("Pawn")); 

    // 2. 메쉬 설정
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionProfileName(TEXT("NoCollision")); 

    // 3. GAS 컴포넌트 생성
    AbilitySystemComponent = CreateDefaultSubobject<UPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);

    // 기지도 체력이 있어야 하므로 AttributeSet을 생성해야 함
    AttributeSet = CreateDefaultSubobject<UPGCharacterAttributeSet>(TEXT("AttributeSet"));
   

}


void ABaseStructure::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        // GAS 초기화 (Owner = this, Avatar = this)
        AbilitySystemComponent->InitAbilityActorInfo(this, this);

        // 초기 스탯 적용 (InitStatEffect가 있다면)
        if (InitStatEffect)
        {
            FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
            ContextHandle.AddSourceObject(this);
            FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatEffect, 1.0f, ContextHandle);

            if (SpecHandle.IsValid())
            {
                AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            }
        }

        // 체력 변경 감지
        if (AttributeSet)
        {
            AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
                UPGCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &ABaseStructure::OnHealthChangedCallback);
        }
    }
}

UAbilitySystemComponent* ABaseStructure::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void ABaseStructure::OnHealthChangedCallback(const FOnAttributeChangeData& Data)
{
    float NewHealth = Data.NewValue;

    // 체력이 0 이하이고 아직 파괴되지 않았다면
    if (NewHealth <= 0.0f)
    {
        DestroyBase();
    }

    // 여기서 체력바 UI 업데이트 로직을 추가
    OnHealthChanged(NewHealth, 1000.0f); // MaxHealth는 가져오는 로직 필요 (일단 하드코딩)
}



void ABaseStructure::DestroyBase()
{
    // 이미 파괴된 상태라면 무시
    if (!this->IsValidLowLevel() || IsActorBeingDestroyed()) return;

    UE_LOG(LogTemp, Warning, TEXT("Base Destroyed! Team: %d"), (int32)TeamID);

    // 1. 게임 모드에 알림 (승패 판정)
    if (OnBaseDestroyed.IsBound())
    {
        OnBaseDestroyed.Broadcast(TeamID);
    }

    // 2. 기지 파괴
    Destroy();
}