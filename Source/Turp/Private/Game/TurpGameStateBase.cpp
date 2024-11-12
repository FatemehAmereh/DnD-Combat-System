// Copyright Erza.


#include "Game/TurpGameStateBase.h"

void ATurpGameStateBase::ResetCombatPacket()
{
	CombatPacket.SourceASC = nullptr;
	CombatPacket.TargetASCs.Empty();
	CombatPacket.TargetLocations.Empty();
	CombatPacket.GameplayEffect = nullptr;
	CombatPacket.isHit.Empty();
}
