// Copyright Erza.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "Game/TurnBasedManager.h"

void UOverlayWidgetController::Init()
{
	AbilityIconPressed.AddDynamic(this, &UOverlayWidgetController::OnAbilityIconPressed);
}

void UOverlayWidgetController::OnAbilityIconPressed(const FGameplayTag& AbilityTag)
{
	// TODO: Get the active ASC from the Turn based manager and activate the ability for that.
	const auto ActiveASC = CastChecked<UTurpAbilitySystemComponent>(TurnBasedManager->GetActivePartyMembersAbilitySystemComponent());
	ActiveASC->ActivateGameplayAbility(AbilityTag);
	// CastChecked<UTurpAbilitySystemComponent>(AbilitySystemComponent)->ActivateGameplayAbility(AbilityTag);
}
