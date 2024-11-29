// Copyright Erza.


#include "TurpTagsManager.h"

#include "GameplayTagsManager.h"

FTurpTagsManager FTurpTagsManager::GameplayTags;

void FTurpTagsManager::InitializeNativeGameplayTags()
{
	GameplayTags.SavingThrow_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Strength"));
	GameplayTags.SavingThrow_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Dexterity"));
	GameplayTags.SavingThrow_Constitution = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Constitution"));
	GameplayTags.SavingThrow_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Intelligence"));
	GameplayTags.SavingThrow_Wisdom = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Wisdom"));
	GameplayTags.SavingThrow_Charisma = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SavingThrow.Charisma"));


	// Ability
	GameplayTags.Ability_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.FireBolt"));
	GameplayTags.Ability_ScorchingRay = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.ScorchingRay"));
	GameplayTags.Ability_Fireball = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Fireball"));
	GameplayTags.Ability_Blindness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Blindness"));
	GameplayTags.Ability_RayOfSickness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.RayOfSickness"));

	// Gameplay Event
	GameplayTags.GameplayEvent_StartTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayEvent.StartTrace"));
	
	// Conditions
	GameplayTags.Condition_Blind = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Condition.Blind"));
	GameplayTags.Condition_Prone = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Condition.Prone"));
	GameplayTags.Condition_Poisoned = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Condition.Poisoned"));

	GameplayTags.DamageModifier = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageModifier"));
}
