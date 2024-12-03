// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TurpHUD.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;
class UTurpUserWidget;
/**
 * 
 */
UCLASS()
class TURP_API ATurpHUD : public AHUD
{
	GENERATED_BODY()
public:
	void InitHUD();
	UOverlayWidgetController* GetOverlayWidgetController();
	
private:
	UPROPERTY()
	TObjectPtr<UTurpUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTurpUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
