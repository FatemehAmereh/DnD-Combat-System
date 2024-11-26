// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "TurpAbilityTypes.h"
#include "TurpGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UTurpGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayEffectProperties EffectProperties;
};
