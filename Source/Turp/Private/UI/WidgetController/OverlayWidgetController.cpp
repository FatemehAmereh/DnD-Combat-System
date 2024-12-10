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

void UOverlayWidgetController::OnChangeTurnPressed()
{
	TurnBasedManager->ChangeTurn();
}

TArray<FGameplayTag> UOverlayWidgetController::GetActiveCharacterAbilityTags()
{
	const auto ActiveASC = TurnBasedManager->GetActivePartyMembersAbilitySystemComponent();

	TArray<FGameplayTag> AbilityTags;
	for (const auto& AbilitySpec : ActiveASC->GetActivatableAbilities())
	{
		const auto& AbilityTag = Cast<UTurpGameplayAbility>(AbilitySpec.Ability)->GetAbilityTag();
		AbilityTags.Add(AbilityTag);
	}
	return AbilityTags;
}

void UOverlayWidgetController::SetTurnBasedManager(ATurnBasedManager* TBManager)
{
	TurnBasedManager = TBManager;
}
