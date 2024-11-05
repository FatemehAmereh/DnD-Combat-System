// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TurpWidgetController.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TURP_API UTurpWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
