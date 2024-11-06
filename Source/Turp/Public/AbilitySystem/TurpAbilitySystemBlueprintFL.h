// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TurpAbilitySystemBlueprintFL.generated.h"

class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class TURP_API UTurpAbilitySystemBlueprintFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TurpAbilitySystemBlueprintFunctionLibrary|WidgetController" )
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
};
