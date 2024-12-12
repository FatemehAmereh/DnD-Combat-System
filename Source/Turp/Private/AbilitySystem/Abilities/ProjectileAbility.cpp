// Copyright Erza.


#include "AbilitySystem/Abilities/ProjectileAbility.h"

#include "AbilitySystemComponent.h"
#include "Actor/TurpProjectile.h"
#include "Interaction/CombatInterface.h"

void UProjectileAbility::SpawnProjectile(const int TargetIndex)
{
	if(const auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		// Find Target Location.
		FVector TargetLocation = FVector::Zero();
		bool DisableOverlap = false;
		const auto [ASC, Location] = TurpGameState->CombatPacket.Targets[TargetIndex];
		if(ASC)
		{
			TargetLocation = ASC->AbilityActorInfo->AvatarActor->GetActorLocation();
		}
		else
		{
			TargetLocation = Location;
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
			GetAvatarActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->SetTargetIndex(TargetIndex);
		Projectile->SetApplyEffect(true);
		if(DisableOverlap)
		{
			Projectile->DisableOverlap();
		}
		else
		{
			Projectile->SetTarget(ASC->GetAvatarActor());
		}
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[FireBolt.cpp] No CombatInterface on Attacker!"))
	}
}