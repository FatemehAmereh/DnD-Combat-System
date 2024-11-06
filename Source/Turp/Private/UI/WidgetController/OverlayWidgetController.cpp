// Copyright Erza.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"

void UOverlayWidgetController::Init()
{
	AbilityIconPressed.AddDynamic(this, &UOverlayWidgetController::OnAbilityIconPressed);
}

void UOverlayWidgetController::OnAbilityIconPressed(const FGameplayTag& AbilityTag)
{
	// TODO: Decide which ability based on Tag
	
	CastChecked<UTurpAbilitySystemComponent>(AbilitySystemComponent)->AddGameplayAbility(TestGameplayAbility);
}
