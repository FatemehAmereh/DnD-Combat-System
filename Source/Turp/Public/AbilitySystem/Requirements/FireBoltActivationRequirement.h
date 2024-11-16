// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectCustomApplicationRequirement.h"
#include "FireBoltActivationRequirement.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UFireBoltActivationRequirement : public UGameplayEffectCustomApplicationRequirement
{
	GENERATED_BODY()

	// Check the saving throws and attack rolls.
	virtual bool CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect, const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const override;
	
};
