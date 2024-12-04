// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurpUserWidget.generated.h"

class UTurpWidgetController;
/**
 * 
 */
UCLASS()
class TURP_API UTurpUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTurpWidgetController> WidgetController;

public:
	void SetWidgetController(UTurpWidgetController* Controller);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
