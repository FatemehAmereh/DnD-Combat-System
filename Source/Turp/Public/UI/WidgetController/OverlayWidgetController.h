// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TurpWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityIconPress, FGameplayTag&, AbilityTag);

/**
 * 
 */
UCLASS()
class TURP_API UOverlayWidgetController : public UTurpWidgetController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<UGameplayAbility> TestGameplayAbility;
	
private:
	void OnAbilityIconPressed(const FGameplayTag& AbilityTag);
};
