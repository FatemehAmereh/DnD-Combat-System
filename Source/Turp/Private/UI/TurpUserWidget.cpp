// Copyright Erza.


#include "UI/TurpUserWidget.h"

void UTurpUserWidget::SetWidgetController(UTurpWidgetController* Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
