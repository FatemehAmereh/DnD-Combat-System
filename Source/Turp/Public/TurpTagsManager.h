// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
struct FTurpTagsManager
{
	static const FTurpTagsManager& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	// Saving Throw
	FGameplayTag SavingThrow_Strength;
	FGameplayTag SavingThrow_Dexterity;
	FGameplayTag SavingThrow_Constitution;
	FGameplayTag SavingThrow_Intelligence;
	FGameplayTag SavingThrow_Wisdom;
	FGameplayTag SavingThrow_Charisma;
	
	// Ability
	FGameplayTag Ability_FireBolt;
	FGameplayTag Ability_ScorchingRay;
	FGameplayTag Ability_Fireball;
	
	// Gameplay Event
	FGameplayTag GameplayEvent_StartTrace;


	// Condition Action
	FGameplayTag Condition_Action_AtkRoll;
	FGameplayTag Condition_Action_StrST;
	FGameplayTag Condition_Action_DexST;
	FGameplayTag Condition_Action_ConST;
	FGameplayTag Condition_Action_IntST;
	FGameplayTag Condition_Action_WisST;
	FGameplayTag Condition_Action_ChaST;
	
	// Conditions
	FGameplayTag Condition_Blind;

	FGameplayTagContainer ConditionActionTags;
private:
	static FTurpTagsManager GameplayTags;
};
