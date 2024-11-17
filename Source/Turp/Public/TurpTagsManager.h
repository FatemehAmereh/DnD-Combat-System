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
	
	// Ability
	FGameplayTag Ability_FireBolt;
	FGameplayTag Ability_ScorchingRay;
	FGameplayTag Ability_BurningHands;
private:
	static FTurpTagsManager GameplayTags;
};
