// Copyright Erza.


#include "AbilitySystem/Abilities/ScorchingRay.h"
#include "AbilitySystemComponent.h"
#include "Actor/TurpProjectile.h"
#include "Interaction/CombatInterface.h"

void UScorchingRay::SpawnProjectiles()
{
	// TODO: Find the middle position between targets to face towards.

	for (int i = 0; i < TurpGameState->CombatPacket.Targets.Num(); ++i)
	{
		SpawnProjectile(i);
	}
}
