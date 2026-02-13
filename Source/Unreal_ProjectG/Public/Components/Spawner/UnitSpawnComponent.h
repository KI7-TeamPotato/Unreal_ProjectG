#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h" 
#include "UnitSpawnComponent.generated.h"

class AUnitCharacter;
class UDataAsset_UnitStartupData;


USTRUCT(BlueprintType)
struct FUnitSpawnInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AUnitCharacter> UnitClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSoftObjectPtr<UDataAsset_UnitStartupData> UnitData;
};


// [변경] UCLASS 설정에 ClassGroup, meta 추가 (에디터 컴포넌트 목록에 뜨게 함)
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECTG_API UUnitSpawnComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UUnitSpawnComponent();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    void SpawnRandomUnit();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    TArray<FUnitSpawnInfo> SpawnList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    float SpawnInterval = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    bool bLoopSpawning = true;

    // [추가] 컴포넌트 방식에서는 박스 컴포넌트를 직접 갖기보다, 범위 벡터만 갖는 게 깔끔함
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    FVector SpawnExtent = FVector(500.f, 500.f, 0.f);

private:
    FTimerHandle SpawnTimerHandle;
};