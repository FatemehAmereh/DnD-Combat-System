// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemComponent.h"

#include "TurpTagsManager.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "AbilitySystem/Data/ConditionInfo.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Kismet/GameplayStatics.h"

void UTurpAbilitySystemComponent::ActivateGameplayAbility(const FGameplayTag& AbilityTag)
{
	// TODO: Optimize this later

	bool found = false;
	for(FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityTag))
		{
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
				found = true;
			}
		}
	}
	if(!found)
	{
		GEngine->AddOnScreenDebugMessage(0,5, FColor::Red, FString("The Ability"
																	  " doesn't exist in activatable abilities.")); 
	}
}

void UTurpAbilitySystemComponent::AddCharacterAbility(const TSubclassOf<UGameplayAbility>& AbilityClass)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
	AbilitySpec.DynamicAbilityTags.AddTag(Cast<UTurpGameplayAbility>(AbilitySpec.Ability)->GetAbilityTag());
	GiveAbility(AbilitySpec);
}

void UTurpAbilitySystemComponent::InitializeConditionActions()
{
	const auto& Tags = FTurpTagsManager::Get();

	// Add Actions and set the stack to 0.
	for(const auto& ActionTag: Tags.ConditionActionTags)
	{
		TMap<EActionStatus, int> Map;
		Map.Add(EActionStatus::Advantage, 0);
		Map.Add(EActionStatus::Disadvantage, 0);
		Map.Add(EActionStatus::Modifier, 0);
		Map.Add(EActionStatus::AutoFail, 0);
		Map.Add(EActionStatus::AutoSave, 0);
		ConditionActionStack.Add(ActionTag, Map);
	}
	
	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UTurpAbilitySystemComponent::OnDurationEffectApplied);
}

void UTurpAbilitySystemComponent::OnDurationEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
	FActiveGameplayEffectHandle ActiveEffectHandle)
{
	const auto GameState = Cast<ATurpGameStateBase>(UGameplayStatics::GetGameState(ASC));
	const auto& Tags = FTurpTagsManager::Get();
	if(const auto TagsComponent = Cast<UTargetTagsGameplayEffectComponent>(Spec.Def->FindComponent(UTargetTagsGameplayEffectComponent::StaticClass())))
	{
		const auto NewlyAddedTagsContainer = TagsComponent->GetConfiguredTargetTagChanges().Added;
		TArray<FGameplayTag> NewlyAddedTags;
		NewlyAddedTagsContainer.GetGameplayTagArray(NewlyAddedTags);
	
		// Tag ex. Condition_blind
		for (const FGameplayTag& ConditionTag : NewlyAddedTags)
		{
			// ActionsArray ex. AtkRoll, Disadv
			TArray<FActionStatusData> ActionsArray;
			GameState->GameplayConditionDataAsset->FindConditionInfoWithTag(ConditionTag, ActionsArray);
	
			for (const auto& ActionStatus : ActionsArray)
			{
				const int StackCount = *ConditionActionStack.Find(ActionStatus.ActionTag)->Find(ActionStatus.StatusEnum);
				ConditionActionStack.Find(ActionStatus.ActionTag)->Add(ActionStatus.StatusEnum, StackCount+1);
			}
		}
	}
}

