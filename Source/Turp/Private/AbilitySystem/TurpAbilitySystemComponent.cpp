// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemComponent.h"

#include "TurpTagsManager.h"
#include "TurpUtilities.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
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
	// AtkRoll, DexST, ...
	for (const auto& ConditionAction : ConditionActionList)
	{
		FActionStatusInfo ActionStatusStruct;
		// Adv, Disadv, ...
		 for (const auto& ActionStatus : ActionStatusList)
		 {
		 	FGameplayTagContainer ConditionTags;
		 	ActionStatusStruct.ActionStatusMap.Add(ActionStatus, ConditionTags);
		 }
		ConditionActionStack.Add(ConditionAction, ActionStatusStruct);
	}
	
	RegisterGenericGameplayTagEvent().AddUObject(this, &UTurpAbilitySystemComponent::OnTagTriggered);
}

const FActionStatusInfo* UTurpAbilitySystemComponent::GetConditionStackForAction(const EActionEnum Action) const
{
	return ConditionActionStack.Find(Action);
}

void UTurpAbilitySystemComponent::AddCondition(const FGameplayTag& ConditionTag)
{
	const int CurrentStackCount = GetGameplayTagCount(ConditionTag);
	if(CurrentStackCount == 0)
	{
		AddLooseGameplayTag(ConditionTag,1);
	}
	else
	{
		SetLooseGameplayTagCount(ConditionTag, CurrentStackCount + 1);
	}
}

void UTurpAbilitySystemComponent::RemoveCondition(const FGameplayTag& ConditionTag)
{
	const int CurrentStackCount = GetGameplayTagCount(ConditionTag);
	SetLooseGameplayTagCount(ConditionTag, CurrentStackCount - 1);
}

void UTurpAbilitySystemComponent::RemoveConditionsForEffect(const FGameplayTag& EffectTag)
{
	const auto GameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	const auto EffectInfo = GameState->GameplayEffectInformation->GetEffectInfoWithTag(EffectTag);
	if(!EffectInfo->Condition.TagsToGrant.IsEmpty())
	{
		for (const auto& ConditionTag : EffectInfo->Condition.TagsToGrant)
		{
			RemoveCondition(ConditionTag);
		}
	}
}

void UTurpAbilitySystemComponent::AddEffect(const FGameplayTag& EffectTag, const uint8 Duration, const bool CanStack, const uint8 DamageSaveDC,  const bool ConditionApplied, const uint8 ConditionSpellSaveDC)
{
	if(EffectTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(Turp, Error, TEXT("%s"), *FString("[AbilitySystemComponent] Cannot add effect. Tag is empty."));
		return;
	}
	
	if(const auto Effect = ActiveEffectStack.Find(EffectTag))
	{
		if(CanStack)
		{
			// Add stack count.
			Effect->StackCount++;
		}
		else
		{
			// Refresh Duration.
			Effect->DurationLeft = Duration;
		}
	}
	else
	{
		ActiveEffectStack.Add(EffectTag, {Duration, 1, DamageSaveDC, ConditionApplied, ConditionSpellSaveDC});	
	}
}

void UTurpAbilitySystemComponent::RemoveEffect(const FGameplayTag& EffectTag, const int StackToRemove)
{
	if(EffectTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(Turp, Error, TEXT("%s"), *FString("[AbilitySystemComponent] Cannot Remove effect. Tag is empty."));
		return;
	}
	
	if(const auto Effect = ActiveEffectStack.Find(EffectTag))
	{
		Effect->StackCount -= StackToRemove;
		if(Effect->StackCount <= 0)
		{
			// Remove Conditions caused by the Effect.
			RemoveConditionsForEffect(EffectTag);
			// Remove the Effect.
			ActiveEffectStack.Remove(EffectTag);
		}
	}
	else
	{
		UE_LOG(Turp, Error, TEXT("%s"), *FString("[AbilitySystemComponent] Effect doesn't exist on ASC."));
	}
}

void UTurpAbilitySystemComponent::OnTurnEnded()
{
	TArray<FGameplayTag> EffectsToRemove;
	// TODO: Fix the exception thrown when the ActiveEffectStack map is empty.
	for (auto& EffectStack : ActiveEffectStack)
	{
		EffectStack.Value.DurationLeft--;

		// Effect's duration has ended.
		if(EffectStack.Value.DurationLeft <= 0)
		{
			if(EffectStack.Value.ConditionGranted)
			{
				// Remove granted conditions.
				RemoveConditionsForEffect(EffectStack.Key);	
			}
			
			// Mark effect for removal.
			EffectsToRemove.Add(EffectStack.Key);
		}
		else
		{
			const auto TurpGameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(GetAvatarActor()));
			UTurpAbilitySystemBlueprintFL::ReapplyActiveGameplayEffect(*TurpGameState, EffectStack.Key, EffectStack.Value, this);
		}
	}

	// Remove effects whose duration ended.
	for (const auto& ToRemove : EffectsToRemove)
	{
		ActiveEffectStack.Remove(ToRemove);
	}
}

void UTurpAbilitySystemComponent::OnTagTriggered(const FGameplayTag Tag, int32 Count)
{
	const auto GameState = Cast<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	
	TMap<EActionEnum, FActionStatusData> ConditionActionInfo;
	if(GameState->GameplayConditionInformation->GetConditionInfoWithTag(Tag, ConditionActionInfo))
	{
		for (const auto& ConditionAction : ConditionActionInfo)
		{
			const auto ActionStatusStruct = ConditionActionStack.Find(ConditionAction.Key);
			const auto ConditionTagContainer = ActionStatusStruct->ActionStatusMap.Find(ConditionAction.Value.StatusEnum);
			if(Count == 1)
			{
				// Tag is Newly Added.
				ConditionTagContainer->AddTag(Tag);
			}
			else if(Count == 0)
			{
				//Tag is being Removed.
				ConditionTagContainer->RemoveTag(Tag);
			}
		}
		
		if(Count == 1)
		{
			UE_LOG(Turp, Log, TEXT("%s: gained condition (%s)"), *GetAvatarActor()->GetName(), *Tag.GetTagName().ToString());
		}
		else if(Count == 0)
		{
			UE_LOG(Turp, Log, TEXT("%s: lost condition (%s)"), *GetAvatarActor()->GetName(), *Tag.GetTagName().ToString());
		}
	}
}

