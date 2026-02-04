// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameplayTags.h"


namespace PGGameplayTags
{
    // 플레이어 어빌리티 태그
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Melee, "Player.Ability.Attack.Melee");

    // 플레이어 무기 게임 플레이 태그
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

    // 이벤트 태그
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");

    // SetByCaller 태그
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_DamageMultiplier, "Shared.SetByCaller.DamageMultiplier");
}

