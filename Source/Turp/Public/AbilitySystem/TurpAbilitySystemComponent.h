// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
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
	
protected:
	//   Action      , <EActionStatus, ConditionTag[]>
	TMap<EActionEnum , FActionStatusInfo> ConditionActionStack;

private:
	// Condition tag callbacks; Called whenever a tag is added for the first time or removed.
	void OnTagTriggered(const FGameplayTag Tag, int32 Count);
};
