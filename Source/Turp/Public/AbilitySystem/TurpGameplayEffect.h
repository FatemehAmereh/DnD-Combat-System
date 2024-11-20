// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "TurpGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UTurpGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int TestVar = 19;
};
