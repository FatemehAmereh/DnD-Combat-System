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
private:
	static FTurpTagsManager GameplayTags;
};
