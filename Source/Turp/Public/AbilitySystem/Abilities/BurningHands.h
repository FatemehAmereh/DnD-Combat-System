// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "BurningHands.generated.h"

/**
 * Work In Progress!
 */
UCLASS()
class TURP_API UBurningHands : public UTurpGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void ConeTrace(FVector MouseHitLocation);
};
