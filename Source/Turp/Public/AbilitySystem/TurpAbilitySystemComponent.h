// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TurpAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UTurpAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ActivateGameplayAbility(const FGameplayTag& AbilityTag);
	void AddCharacterAbility(TSubclassOf<UGameplayAbility> AbilityClass);
};
