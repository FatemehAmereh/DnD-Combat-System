// Copyright Erza.


#include "AbilitySystem/Abilities/FireBolt.h"

#include "AbilitySystemComponent.h"
#include "Actor/TurpProjectile.h"
#include "Game/TurpGameStateBase.h"
#include "Interaction/CombatInterface.h"

void UFireBolt::SpawnProjectile()
{
	if(const auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());
		const FVector TargetLocation = FindTargetLocation();
		const FRotator Rotation = (TargetLocation - SocketLocation).Rotation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		check(ProjectileClass);
		auto Projectile = GetWorld()->SpawnActorDeferred<ATurpProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->SetGameplayEffectParams(GameplayEffectParams);
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

FVector UFireBolt::FindTargetLocation() const
{
	if(!TurpGameState->CombatPacket.TargetASCs.IsEmpty())
	{
		return TurpGameState->CombatPacket.TargetASCs[0]->AbilityActorInfo->AvatarActor->GetActorLocation();
	}
	return TurpGameState->CombatPacket.TargetLocations[0];
}
