// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileAbility.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "ScorchingRay.generated.h"

class ATurpProjectile;
/**
 * 
 */
UCLASS()
class TURP_API UScorchingRay : public UProjectileAbility
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles();
};
