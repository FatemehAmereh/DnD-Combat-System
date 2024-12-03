// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "TurpWidgetController.generated.h"

class ATurnBasedManager;
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
	void SetTurnBasedManager(ATurnBasedManager* TBManager);
	
protected:
	// TODO: Get a reference to the TurnBasedManger
	UPROPERTY()
	TObjectPtr<ATurnBasedManager> TurnBasedManager;
};
