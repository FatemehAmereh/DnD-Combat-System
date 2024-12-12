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
	FGameplayTag Ability_Blindness;
	FGameplayTag Ability_RayOfSickness;
	FGameplayTag Ability_Bless;
	
	// Gameplay Event
	FGameplayTag GameplayEvent_StartTrace;
	
	// Conditions
	FGameplayTag Condition_Blind;
	FGameplayTag Condition_Prone;
	FGameplayTag Condition_Poisoned;
	// Non-standard Conditions such as Bless that gives 1d4 to all saves and AtkRolls.
	FGameplayTag Condition_Ability_Bless;

	// Damage modifier tag used in default GameplayEffect asset for applying damage.
	FGameplayTag DamageModifier;

private:
	static FTurpTagsManager GameplayTags;
};
