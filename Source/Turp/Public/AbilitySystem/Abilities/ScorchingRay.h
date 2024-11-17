// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "ScorchingRay.generated.h"

class ATurpProjectile;
/**
 * 
 */
UCLASS()
class TURP_API UScorchingRay : public UTurpGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Scorching Ray")
	TSubclassOf<ATurpProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles();
};
