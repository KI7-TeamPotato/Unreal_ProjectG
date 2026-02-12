#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h" 
#include "Types/PGEnumTypes.h"
#include "BaseStructure.generated.h"

// 델리게이트 선언 (기지 파괴 알림용)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBaseDestroyed, ETeamType, DestroyedTeam);


UCLASS()
class UNREAL_PROJECTG_API ABaseStructure : public APawn, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ABaseStructure();

protected:
    virtual void BeginPlay() override;

protected:
    // --- [1] 기지 요소 ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    TObjectPtr<class UCapsuleComponent> CapsuleComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
    TObjectPtr<class UStaticMeshComponent> MeshComp;

    // --- [2] GAS 컴포넌트 ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    TObjectPtr<class UPGAbilitySystemComponent> AbilitySystemComponent;

    
    UPROPERTY()
    TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

public:
    // --- [3] 게임 로직 ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    ETeamType TeamID;

    UPROPERTY(BlueprintAssignable)
    FOnBaseDestroyed OnBaseDestroyed;

    UPROPERTY(EditDefaultsOnly, Category = "GAS")
    TSubclassOf<class UGameplayEffect> InitStatEffect;

public:
   
    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    // 체력 변경 콜백 (AttributeSet 델리게이트용)
    void OnHealthChangedCallback(const struct FOnAttributeChangeData& Data);

    // 블루프린트용 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "Base")
    void OnHealthChanged(float NewHealth, float MaxHealth);

    // 파괴 처리
    void DestroyBase();
};