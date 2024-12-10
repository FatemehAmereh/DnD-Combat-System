// Copyright Erza.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "Character/TurpCharacterBase.h"
#include "Game/TurnBasedManager.h"

void UOverlayWidgetController::Init()
{
	//AbilityIconPressed.AddDynamic(this, &UOverlayWidgetController::OnAbilityIconPressed);
}

void UOverlayWidgetController::OnAbilityIconPressed(const FGameplayTag& AbilityTag)
{
	const auto ActiveASC = CastChecked<UTurpAbilitySystemComponent>(TurnBasedManager->GetActivePartyMembersAbilitySystemComponent());
	ActiveASC->ActivateGameplayAbility(AbilityTag);
}

FGameplayTagContainer UOverlayWidgetController::OnChangeTurnPressed()
{
	TurnBasedManager->ChangeTurn();
	
	// TODO: Change available abilities on the UI for the active ASC.
	const auto ActiveASC = TurnBasedManager->GetActivePartyMembersAbilitySystemComponent();

	FGameplayTagContainer AbilityTagContainer;
	for (const auto& AbilitySpec : ActiveASC->GetActivatableAbilities())
	{
		const auto& AbilityTag = Cast<UTurpGameplayAbility>(AbilitySpec.Ability)->GetAbilityTag();
		AbilityTagContainer.AddTag(AbilityTag);
	}
	return AbilityTagContainer;
}
