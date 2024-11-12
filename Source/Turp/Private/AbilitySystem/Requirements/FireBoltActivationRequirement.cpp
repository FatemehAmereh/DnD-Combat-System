// Copyright Erza.


#include "AbilitySystem/Requirements/FireBoltActivationRequirement.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/TurpAttributeSet.h"

bool UFireBoltActivationRequirement::CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect,
                                                                           const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const
{
	// Whose ASC is that?!
	//Spec.GetContext().GetInstigatorAbilitySystemComponent()
	const auto AttributeSet = Cast<UTurpAttributeSet>(ASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const float ACToBeat = UTurpAbilitySystemBlueprintFL::RollDN(20) + AttributeSet->GetProficiencyBonus() + AttributeSet->GetIntelligence();
	return ACToBeat >= AttributeSet->GetArmorClass();
}
