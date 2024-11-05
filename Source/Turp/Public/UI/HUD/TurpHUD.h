// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TurpHUD.generated.h"

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
	UOverlayWidgetController* GetOverlayWidgetController() const;
	
private:
	UPROPERTY()
	TObjectPtr<UTurpUserWidget> OverlayWidget;
	
	UPROPERTY()
	TSubclassOf<UTurpUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY()
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
