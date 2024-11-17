// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

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
