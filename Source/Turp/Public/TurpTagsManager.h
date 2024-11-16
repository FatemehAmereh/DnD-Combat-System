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

	FGameplayTag SavingThrow_Strength;
	
private:
	static FTurpTagsManager GameplayTags;
};
