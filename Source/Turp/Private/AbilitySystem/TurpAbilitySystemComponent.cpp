// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemComponent.h"

void UTurpAbilitySystemComponent::AddGameplayAbility(const TSubclassOf<UGameplayAbility> AbilityClass)
{
	auto AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
	GiveAbility(AbilitySpec);
}
