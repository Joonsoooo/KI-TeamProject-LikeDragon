// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseGamePlayTags.h"

namespace BaseGameplayTags
{
	//이준수, Ryoma Ability Default Input Tags
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Move, "chara.Ability.DefaultMode.Move");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Look, "chara.Ability.DefaultMode.Look");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Walk, "chara.Ability.DefaultMode.Walk");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Run, "chara.Ability.DefaultMode.Run");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Equip_Katana_tachi, "Chara.Ability.Input.Equip.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_UnEquip_Katana_tachi, "Chara.Ability.Input.UnEquip.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_CombatMode_Shift, "Chara.Ability.Input.CombatMode.Shift");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_LightAttack_Katana_tachi, "Chara.Ability.Input.LightAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_HeavyAttack_Katana_tachi, "Chara.Ability.Input.HeavyAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Sway, "Chara.Ability.Input.Sway");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_HactAttack_Katana_tachi, "Chara.Ability.Input.HactAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Hold, "Chara.Ability.Input.Hold");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Hold_Targeting, "Chara.Ability.Input.Hold.Targeting");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Hold_Block, "Chara.Ability.Input.Hold.Block");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Input_Hold_ChargeAttack, "Chara.Ability.Input.Hold.ChargeAttack");

	// 이준수, Ryoma Ability
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Spawned_Katana_tachi_fk, "Chara.Ability.Spawned.Katana.tachi_fk");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Equip_Katana_tachi_fk, "Chara.Ability.Equip.Katana.tachi.fk");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_UnEquip_Katana_tachi_fk, "Chara.Ability.UnEquip.Katana.tachi.fk");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Light_Katana_tachi, "Chara.Ability.Attack.Light.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Heavy_Katana_tachi, "Chara.Ability.Attack.Heavy.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Charge, "Chara.Ability.Attack.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_ChargeAttack_Katana_tachi, "Chara.Ability.Attack.ChargeAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_UnChargeAttack_Katana_tachi, "Chara.Ability.Attack.UnChargeAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Hact_Katana_tachi, "Chara.Ability.Attack.Hact.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Sway, "Chara.Ability.Attack.Sway");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Targeting, "Chara.Ability.Attack.Targeting");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Attack_Block, "Chara.Ability.Attack.Block");

	// 이준수, Ryoma Weapon Ability
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Weapon_Katana_tachi_fk, "Chara.Ability.Weapon.Katana.tachi.fk");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_Weapon_Katana_tachi, "Chara.Ability.Weapon.Katana.tachi");

	// 정찬희, 
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Input_Interact, "chara.Ability.DefaultMode.Input.Interact");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Input_OpenMenu , "Chara.Ability.DefaultMode.Input.OpenMenu"); // 정찬희
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Input_Selcet , "Chara.Ability.DefaultMode.Input.Select");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Ability_DefaultMode_Input_ESC , "Chara.Ability.DefaultMode.Input.ESC")

	
	// 이준수, Character Event (이벤트가 발생했을 때의 태그)
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Equip_Katana, "Chara.Event.Equip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_UnEquip_Katana, "Chara.Event.UnEquip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_HitAttack, "Chara.Event.HitAttack");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_LastHitAttack, "Chara.Event.LastHitAttack");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_LightAttack_1, "Chara.Event.LightAttack.1");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_LightAttack_2, "Chara.Event.LightAttack.2");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_LightAttack_3, "Chara.Event.LightAttack.3");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_LightAttack_4, "Chara.Event.LightAttack.4");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Sway, "Chara.Event.Sway");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Attack_ChargeAttack_Katana_tachi, "Chara.Event.Attack.ChargeAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Attack_UnChargeAttack_Katana_tachi, "Chara.Event.Attack.UnChargeAttack.Katana.tachi");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Attack_Hact, "Chara.Event.Attack.Hact");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Event_Attack_Hact_Katana_tachi, "Chara.Event.Attack.Hact.Katana.tachi");

	//이준수 , Character Status
	UE_DEFINE_GAMEPLAY_TAG(Chara_Status_Targeting, "Chara.Status.Targeting");
	UE_DEFINE_GAMEPLAY_TAG(Chara_Status_Swaying, "Chara.Status.Swaying");
	
	//김동휘, Enemy Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Block, "Enemy.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Rage, "Enemy.Ability.Rage");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Rage, "Enemy.Event.Rage");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");

	//김동휘, Shared Tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitHeavyReact, "Shared.Ability.HitHeavyReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHeavyHit, "Shared.Event.MeleeHeavyHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitHeavyReact, "Shared.Event.HitHeavyReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SuccessBlock, "Shared.Event.SuccessBlock"); // 이준트 막기 성공 (패링)
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_AttackType_Light, "Shared.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_AttackType_Heavy, "Shared.SetByCaller.AttackType.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_AttackType_Hact, "Shared.SetByCaller.AttackType.Hact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_HactCount, "Shared.SetByCaller.HactCount");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_HealthRecovery, "Shared.SetByCaller.HealthRecovery");

	// 이준수 Shared Status
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Blocking, "Shared.Status.Blocking");
	// 이준수, 피격 방향 
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back")
}
