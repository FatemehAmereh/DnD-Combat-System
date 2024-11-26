// Copyright Erza.


#include "Game/TurpGameStateBase.h"

void ATurpGameStateBase::ResetCombatPacket()
{
	CombatPacket.SourceASC = nullptr;
	CombatPacket.Targets.Empty();
	// Do I need this?
	CombatPacket.AbilityProperties.Reset();
}
