// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

//
// 태그를 정의하는 곳
//
namespace PGGameplayTags
{
    // 플레이어 무기 게임 플레이 태그 
    UNREAL_PROJECTG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

    // 이벤트 태그
    UNREAL_PROJECTG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit); // 무기가 타겟에 적중 성공 헀을 때 발생하는 이벤트 태그
}
