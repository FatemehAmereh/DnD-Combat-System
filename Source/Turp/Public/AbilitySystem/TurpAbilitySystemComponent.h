// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TurpAbilitySystemComponent.generated.h"

enum class EActionStatus;
/**
 * 
 */
UCLASS()
class TURP_API UTurpAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ActivateGameplayAbility(const FGameplayTag& AbilityTag);
	void AddCharacterAbility(const TSubclassOf<UGameplayAbility>& AbilityClass);
	void InitializeConditionActions();
	
protected:
	//   ActionTag   ,      ActionEnum   , StackCount
	TMap<FGameplayTag, TMap<EActionStatus, int>> ConditionActionStack;

private:
	// Condition tag callbacks.
	void OnDurationEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle ActiveEffectHandle);
	void OnEffectRemoved(const FActiveGameplayEffect& ActiveEffect);
	void UpdateConditionActionStack(const bool ShouldAddStack, const FGameplayEffectSpec& Spec);
};
