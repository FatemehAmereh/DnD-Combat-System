// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "Fireball.generated.h"

class AProjectileTargetActor;
class ATurpProjectile;
/**
 * 
 */
UCLASS()
class TURP_API UFireball : public UTurpGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Fireball")
	TSubclassOf<ATurpProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Fireball")
	TSubclassOf<AProjectileTargetActor> ProjectileTargetClass;
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FVector MouseHitLocation);
};
