// Copyright Erza.


#include "Game/TurpGameStateBase.h"

void ATurpGameStateBase::ResetCombatPacket()
{
	CombatPacket.SourceASC = nullptr;
	CombatPacket.Targets.Empty();
	// Do I need this here?
	CombatPacket.AbilityProperties.Reset();
	CombatPacket.EffectProperties.Reset();
}
