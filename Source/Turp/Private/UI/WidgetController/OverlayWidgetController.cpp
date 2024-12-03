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
	const auto ActiveASC = CastChecked<UTurpAbilitySystemComponent>(TurnBasedManager->GetActivePartyMembersAbilitySystemComponent());
	ActiveASC->ActivateGameplayAbility(AbilityTag);
}
