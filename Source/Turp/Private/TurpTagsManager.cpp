// Copyright Erza.


#include "TurpTagsManager.h"

#include "GameplayTagsManager.h"

FTurpTagsManager FTurpTagsManager::GameplayTags;

void FTurpTagsManager::InitializeNativeGameplayTags()
{
	GameplayTags.SavingThrow_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Strength"));
}
