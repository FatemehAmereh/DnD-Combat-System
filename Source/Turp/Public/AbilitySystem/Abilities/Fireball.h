// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileAbility.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "Fireball.generated.h"

class AProjectileTargetActor;
/**
 * 
 */
UCLASS()
class TURP_API UFireball : public UProjectileAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Fireball")
	TSubclassOf<AProjectileTargetActor> ProjectileTargetClass;

	UPROPERTY(BlueprintReadWrite)
	FVector MouseHitLocation = FVector::Zero();
	
	virtual void SpawnProjectile(const int TargetIndex) override;
};
