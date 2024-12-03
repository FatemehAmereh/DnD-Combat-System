// Copyright Erza.


#include "Game/TurpGameStateBase.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Character/EnemyCharacter.h"
#include "Character/TurpCharacter.h"

void ATurpGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATurpGameStateBase::ResetCombatPacket()
{
	CombatPacket.SourceASC = nullptr;
	CombatPacket.Targets.Empty();
	// Do I need this here?
	CombatPacket.AbilityProperties.Reset();
	CombatPacket.EffectProperties.Reset();
}