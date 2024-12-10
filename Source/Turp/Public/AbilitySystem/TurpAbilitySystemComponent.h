// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TurpAbilityTypes.h"
#include "TurpAbilitySystemComponent.generated.h"

enum class EActionEnum;
enum class EStatusEnum;

USTRUCT(BlueprintType)
struct FActionStatusInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EStatusEnum , FGameplayTagContainer> ActionStatusMap;
};
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
	const FActionStatusInfo* GetConditionStackForAction(const EActionEnum Action) const;

	void AddCondition(const FGameplayTag& ConditionTag);
	void RemoveCondition(const FGameplayTag& ConditionTag);

	void AddEffect(const FGameplayTag& EffectTag, const uint8 Duration, const bool CanStack);
	
protected:
	//   Action      , <EActionStatus, ConditionTag[]>
	TMap<EActionEnum , FActionStatusInfo> ConditionActionStack;

	TMap<FGameplayTag, FEffectStackElement> ActiveEffectStack;

private:
	// Condition tag callbacks; Called whenever a tag is added for the first time or removed.
	void OnTagTriggered(const FGameplayTag Tag, int32 Count);
};
