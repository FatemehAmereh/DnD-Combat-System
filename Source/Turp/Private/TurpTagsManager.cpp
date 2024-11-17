// Copyright Erza.


#include "TurpTagsManager.h"

#include "GameplayTagsManager.h"

FTurpTagsManager FTurpTagsManager::GameplayTags;

void FTurpTagsManager::InitializeNativeGameplayTags()
{
	GameplayTags.SavingThrow_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Strength"));


	// Ability
	GameplayTags.Ability_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.FireBolt"));
	
	GameplayTags.Ability_ScorchingRay = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.ScorchingRay"));
}
