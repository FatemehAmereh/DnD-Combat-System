// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TurpWidgetController.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TURP_API UTurpWidgetController : public UObject
{
	GENERATED_BODY()
public:
	virtual void Init();
};
