// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"


namespace BaseGameplayTags
{
	// 이준수, Ryoma Ability Default Input Tags
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Move); // 이준수, 추후에 Input로 이름 변경 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Look);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Walk);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Run);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Input_Interact); // 정찬희
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Input_OpenMenu); // 정찬희
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Input_Selcet);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_DefaultMode_Input_ESC);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Equip_Katana_tachi); // 이준수, tachi 장착
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_UnEquip_Katana_tachi); // 이준수, tachi 장착 해제
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_CombatMode_Shift); // 이준수, 전투 모드일 때 적 포커싱
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_LightAttack_Katana_tachi);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_HeavyAttack_Katana_tachi);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Sway);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_HactAttack_Katana_tachi); // 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Hold); // 이준수, 꾹 누르고 있을 때
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Hold_Targeting);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Hold_Block); // 이준수, 막기는 꾹 누르고 있을 때 작동 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Input_Hold_ChargeAttack); // 이준수, 차지는 꾹 누르고 있을 때 작동 

	// 이준수, Ryoma Ability
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Spawned_Katana_tachi_fk); // tachi_fk_FK spawn 능력
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Equip_Katana_tachi_fk); // 카타나 Equip  능력
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_UnEquip_Katana_tachi_fk); // 카타나 UnEquip  능력
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Light_Katana_tachi); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Heavy_Katana_tachi); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Charge); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_ChargeAttack_Katana_tachi); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_UnChargeAttack_Katana_tachi); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Hact_Katana_tachi); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Sway); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Targeting);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Attack_Block)

	
	// 이준수, Ryoma Weapon Ability
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Weapon_Katana_tachi_fk); // 무기 이름 Ability
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Ability_Weapon_Katana_tachi); // 무기 이름 Ability
	
	// Character Event (이벤트가 발생했을 때의 태그)
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Equip_Katana);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_UnEquip_Katana);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_HitAttack); // 이준수, 한대 때리고 다음 콤보로 연결되기 위한 태그
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_LastHitAttack); // 이준수, 마지막 콤보 이후 후딜을 넣기 위한 태그
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_LightAttack_1); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_LightAttack_2); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_LightAttack_3); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_LightAttack_4); 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Sway); // 이준수, Sway
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Attack_ChargeAttack_Katana_tachi);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Attack_UnChargeAttack_Katana_tachi);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Attack_Hact);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Event_Attack_Hact_Katana_tachi);

	// 이준수, Character Status
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Status_Targeting); // 이준수, Sway
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chara_Status_Swaying); // 이준수, Sway
	
	//김동휘, Enemy Tags
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Block);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Rage);
	
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_Rage);
	
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);

	//김동휘, Shared Tags
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact); // 이준수, 약공격들?
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitHeavyReact); // 이준수, 강공격들?
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHeavyHit);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitHeavyReact);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SuccessBlock); //
	
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage); // 이준수 Call하는 값으로 Set한다 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_AttackType_Light); // 이준수 Call하는 값으로 Set한다 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_AttackType_Heavy); // 이준수 Call하는 값으로 Set한다
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_AttackType_Hact); // 이준수 Call하는 값으로 Set한다
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_HactCount); // 이준수 Call하는 값으로 Set한다
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_HealthRecovery); // 이준수 Call하는 값으로 Set한다
	
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Blocking);
	// 이준수, 피격 방향 
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front)
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left)
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right)
	L11_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back)
}
