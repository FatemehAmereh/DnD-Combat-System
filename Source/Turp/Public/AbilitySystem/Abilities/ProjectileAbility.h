// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "ProjectileAbility.generated.h"

class ATurpProjectile;
/**
 * 
 */
UCLASS()
class TURP_API UProjectileAbility : public UTurpGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATurpProjectile> ProjectileClass;
	
	UFUNCTION(BlueprintCallable)
	virtual void SpawnProjectile(const int TargetIndex = 0);
};
