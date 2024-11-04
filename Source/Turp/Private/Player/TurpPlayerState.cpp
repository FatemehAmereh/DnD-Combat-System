// Copyright Erza.


#include "Player\TurpPlayerState.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"

ATurpPlayerState::ATurpPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTurpAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	
	AttributeSet = CreateDefaultSubobject<UTurpAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ATurpPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ATurpPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

int32 ATurpPlayerState::GetPlayerLevel() const
{
	return Level;
}
