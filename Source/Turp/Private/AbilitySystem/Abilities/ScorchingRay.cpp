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
		// Find Target
		FVector TargetLocation = FVector::Zero();
		bool DisableOverlap = false;
		const auto TargetData = TurpGameState->CombatPacket.Targets[i];
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

		const auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
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

		Projectile->SetTargetIndex(i);
		Projectile->SetApplyEffect(true);
		if(DisableOverlap)
		{
			Projectile->DisableOverlap();
		}
		else
		{
			Projectile->SetTarget(TargetData.ASC->GetAvatarActor());
		}
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
