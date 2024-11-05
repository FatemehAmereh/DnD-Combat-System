// Copyright Erza.


#include "UI/HUD/TurpHUD.h"
#include "UI/TurpUserWidget.h"
#include "Blueprint/UserWidget.h"

void ATurpHUD::InitHUD()
{
	auto OverlayWidget = CreateWidget(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	
}

UOverlayWidgetController* ATurpHUD::GetOverlayWidgetController() const
{
	return OverlayWidgetController;
}
