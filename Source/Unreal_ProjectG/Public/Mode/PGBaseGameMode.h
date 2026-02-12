// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/PGEnumTypes.h"
#include "PGBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API APGBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    APGBaseGameMode();

    // --- [1] 인구수 제한  ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitCount")
    int32 MAX_ALLY_COUNT = 15; //아군

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitCount")
    int32 MAX_ENEMY_COUNT = 15; //적군

    //현재 유닛 수 확인
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameRule")
    int32 CurrentAllyCount = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameRule")
    int32 CurrentEnemyCount = 0;

    bool CanSpawnUnit(ETeamType Team);
    void RegisterUnit(ETeamType Team);
    void UnregisterUnit(ETeamType Team);

    // ---  클리어 등급 설정 (시간 제한) ---
    // 3별을 받기 위한 제한 시간 (초 단위, 예: 60초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameRule|Grade")
    float ClearTimeLimit_3Stars = 60.0f;

    // 2별을 받기 위한 제한 시간 (초 단위, 예: 180초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameRule|Grade")
    float ClearTimeLimit_2Stars = 180.0f;
   

    // 현재 플레이 시간(초)을 반환하는 함수 (UI 표시용)
    UFUNCTION(BlueprintPure, Category = "GameRule|Time")
    float GetCurrentPlayTime() const;

public:
    // --- [2] 승패 판정 로직 ---
    // 기지가 파괴되었을 때 호출되는 함수
    void OnGameOver(ETeamType DefeatedTeam);

   

protected:
    // 게임 종료 상태 플래그 (중복 호출 방지)
    bool bIsGameOver = false;

    // 게임 시작 시간 기록
    float GameStartTime = 0.0f;
 
    // [BP 연동] 결과 UI를 띄우기 위한 이벤트
     // bIsVictory: 승리 여부
     // StarCount: 획득한 별 개수 (0: 패배, 1~3: 승리)
    UFUNCTION(BlueprintImplementableEvent, Category = "GameRule")
    void BP_ShowResultUI(bool bIsVictory, int32 StarCount);
};
