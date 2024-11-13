// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "FireBolt.generated.h"

class ATurpProjectile;
/**
 * 
 */
UCLASS()
class TURP_API UFireBolt : public UTurpGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Fire Bolt")
	TSubclassOf<ATurpProjectile> ProjectileClass;
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile();

private:
	FVector FindTargetLocation() const;
};
