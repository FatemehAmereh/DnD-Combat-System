// Copyright Erza.


#include "UI/HUD/TurpHUD.h"
#include "UI/TurpUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void ATurpHUD::InitHUD()
{
	OverlayWidget = CreateWidget<UTurpUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	
	OverlayWidgetController = GetOverlayWidgetController();
	OverlayWidgetController->Init();
	OverlayWidget->SetWidgetController(OverlayWidgetController);
}

UOverlayWidgetController* ATurpHUD::GetOverlayWidgetController()
{
	if(!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	}
	return OverlayWidgetController;
}
