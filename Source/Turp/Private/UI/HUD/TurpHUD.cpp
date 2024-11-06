// Copyright Erza.


#include "UI/HUD/TurpHUD.h"
#include "UI/TurpUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void ATurpHUD::InitHUD(UAbilitySystemComponent* ASC)
{
	OverlayWidget = CreateWidget<UTurpUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	
	OverlayWidgetController = GetOverlayWidgetController(ASC);
	OverlayWidgetController->Init();
}

UOverlayWidgetController* ATurpHUD::GetOverlayWidgetController(UAbilitySystemComponent* ASC)
{
	if(!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetAbilitySystemComponent(ASC);
	}
	return OverlayWidgetController;
}
