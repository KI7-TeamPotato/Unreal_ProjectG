
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PGGameplayAbility.h"
#include "PGHeroGameplayAbility.generated.h"

class UHeroEquipmentComponent;
class AHeroController;
class AHeroCharacter;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UPGHeroGameplayAbility : public UPGGameplayAbility
{
	GENERATED_BODY()
	
public:
    // TODO : 클래스를 우리의 플레이어 캐릭터 타입으로 변경
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    AHeroCharacter* GetHeroCharacterFromActorInfo();

    // TODO : 클래스를 우리의 플레이어 컨트로러 타입으로 변경
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    AHeroController* GetHeroControllerFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    UHeroEquipmentComponent* GetHeroEquipmentComponentFromActorInfo() const;

    // TODO : 공격의 속성이나 다른 효과가 추가된다면 매개변수를 확장
    UFUNCTION(BlueprintPure, Category = "PG|Ability")
    FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float SkillMultiflier);

private:
    TWeakObjectPtr<AHeroCharacter> CachedHeroCharacter;
    TWeakObjectPtr<AHeroController> CachedHeroController;
};
