// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameplayTags.h"


namespace PGGameplayTags
{
    // 인풋 태그
    UE_DEFINE_GAMEPLAY_TAG(InputTag_BaseAttack, "Input.BaseAttack");
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_1, "Input.Skill.1");
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_2, "Input.Skill.2");

    // 플레이어 어빌리티 태그
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BasicAttack_Melee, "Player.Ability.BasicAttack.Melee");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_1, "Player.Ability.Skill.1");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_2, "Player.Ability.Skill.2");

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_EquipWeapon, "Player.Ability.EquipWeapon");

    // 플레이어 무기 게임 플레이 태그
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

    // 유닛 어빌리티 태그
    UE_DEFINE_GAMEPLAY_TAG(Unit_Ability_BasicAttack_Melee, "Unit.Ability.BasicAttack.Melee");

    // 공유 어빌리티 태그
    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_SpawnWeapon, "Shared.Ability.SpawnWeapon");


    // 이벤트 태그
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_AttackTraceToggle, "Shared.Event.AttackTraceToggle");
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_WeaponSpawn, "Shared.Event.WeaponSpawn");

    // SetByCaller 태그
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_DamageMultiplier, "Shared.SetByCaller.DamageMultiplier");
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_MaxHealthMultiplier, "Shared.SetByCaller.MaxHealthMultiplier");
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_AttackPowerMultiplier, "Shared.SetByCaller.AttackPowerMultiplier");


    //유닛 등급 태그
    UE_DEFINE_GAMEPLAY_TAG(Unit_Tier_Normal, "Unit.Tier.Normal");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Tier_Rare, "Unit.Tier.Rare");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Tier_Epic, "Unit.Tier.Epic");

    //유닛 속성 태그
    UE_DEFINE_GAMEPLAY_TAG(Unit_Element_Fire, "Unit.Element.Fire");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Element_Water, "Unit.Element.Water");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Element_Electric, "Unit.Element.Electric");

    //유닛 병과 태그
    UE_DEFINE_GAMEPLAY_TAG(Unit_Branch_Melee, "Unit.Branch.Melee");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Branch_Ranged, "Unit.Branch.Ranged");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Branch_Mage, "Unit.Branch.Mage");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Branch_Tank, "Unit.Branch.Tank");

    //유닛 진영 태그
    UE_DEFINE_GAMEPLAY_TAG(Unit_Side_Ally, "Unit.Side.Ally");
    UE_DEFINE_GAMEPLAY_TAG(Unit_Side_Foe, "Unit.Side.Foe");
}

