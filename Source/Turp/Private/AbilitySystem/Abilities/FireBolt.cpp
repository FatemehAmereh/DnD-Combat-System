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
		// Find Target
		FVector TargetLocation = FVector::Zero();
		bool DisableOverlap = false;
		const auto TargetData = TurpGameState->CombatPacket.Targets[0];
		if(TargetData.ASC)
		{
			TargetLocation = TargetData.ASC->AbilityActorInfo->AvatarActor->GetActorLocation();
		}
		else
		{
			TargetLocation =  TargetData.Location;
			DisableOverlap = true;
		}
		//
		
		const FVector SocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());
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

		Projectile->SetGameplayAbilityProperties(GameplayAbilityProperties);
		if(DisableOverlap)
		{
			Projectile->DisableOverlap();
		}
		else
		{
			Projectile->SetTargetASC(TargetData.ASC);
		}
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

FVector UFireBolt::FindTargetLocation() const
{
	const auto TargetData = TurpGameState->CombatPacket.Targets[0];
	if(TargetData.ASC)
	{
		return TargetData.ASC->AbilityActorInfo->AvatarActor->GetActorLocation();
	}
	return TargetData.Location;
}
