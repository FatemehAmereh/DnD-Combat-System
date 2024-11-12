// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TurpPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityActionSignature);
/**
 * 
 */
UCLASS()
class TURP_API ATurpPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAbilityActionSignature AbilityActionTriggered;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AbilityAction;
	
	void Move(const struct FInputActionValue& InputActionValue);

	void AbilityActionTrigger();
};
