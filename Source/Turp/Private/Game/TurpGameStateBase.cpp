// Copyright Erza.


#include "Game/TurpGameStateBase.h"

void ATurpGameStateBase::ResetCombatPacket()
{
	CombatPacket.SourceASC = nullptr;
	CombatPacket.Targets.Empty();
	CombatPacket.GameplayEffect = nullptr;
	CombatPacket.isHit.Empty();
}
