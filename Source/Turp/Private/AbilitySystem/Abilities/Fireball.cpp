// Copyright Erza.


#include "AbilitySystem/Abilities/Fireball.h"

#include "Actor/ProjectileTargetActor.h"
#include "Actor/TurpProjectile.h"
#include "Interaction/CombatInterface.h"

void UFireball::SpawnProjectile(const int TargetIndex)
{
	const auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	const FVector SocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());
	const FRotator Rotation = (MouseHitLocation - SocketLocation).Rotation();

	// Projectile Target Actor
	FTransform ProjectileTargetSpawnTransform;
	ProjectileTargetSpawnTransform.SetLocation(MouseHitLocation);
	ProjectileTargetSpawnTransform.SetRotation(FQuat::Identity);
	check(ProjectileTargetClass);
	auto ProjectileTarget = GetWorld()->SpawnActorDeferred<AProjectileTargetActor>(
		ProjectileTargetClass,
		ProjectileTargetSpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	ProjectileTarget->FinishSpawning(ProjectileTargetSpawnTransform);

	// Projectile
	FTransform ProjectileSpawnTransform;
	ProjectileSpawnTransform.SetLocation(SocketLocation);
	ProjectileSpawnTransform.SetRotation(Rotation.Quaternion());
	check(ProjectileClass);
	auto Projectile = GetWorld()->SpawnActorDeferred<ATurpProjectile>(
		ProjectileClass,
		ProjectileSpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->SetTarget(ProjectileTarget);
	Projectile->FinishSpawning(ProjectileSpawnTransform);
}
