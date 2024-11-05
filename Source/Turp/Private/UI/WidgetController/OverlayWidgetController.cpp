// Copyright Erza.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"

void UOverlayWidgetController::OnAbilityIconPressed(const FGameplayTag& AbilityTag)
{
	// TODO: Decide which ability based on Tag

	CastChecked<UTurpAbilitySystemComponent>(AbilitySystemComponent)->AddGameplayAbility(TestGameplayAbility);
}
