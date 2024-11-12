// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TurpWidgetController.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySet.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityIconPress, const FGameplayTag&, AbilityTag);

/**
 * 
 */
UCLASS()
class TURP_API UOverlayWidgetController : public UTurpWidgetController
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UPROPERTY(BlueprintCallable)
	FAbilityIconPress AbilityIconPressed;
	
private:
	UFUNCTION()
	void OnAbilityIconPressed(const FGameplayTag& AbilityTag);
};
