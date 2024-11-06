// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TurpPlayerState.h"
#include "UI/HUD/TurpHUD.h"

UOverlayWidgetController* UTurpAbilitySystemBlueprintFL::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if(auto PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(auto HUD = PlayerController->GetHUD<ATurpHUD>())
		{
			auto ASC = PlayerController->GetPlayerState<ATurpPlayerState>()->GetAbilitySystemComponent();
			check(ASC);
			return HUD->GetOverlayWidgetController(ASC);
		}
	}

	return nullptr;
}
