// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

void UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_SourceASC(ATurpGameStateBase* GameState, UAbilitySystemComponent* ASC)
{
	GameState->CombatPacket.SourceASC = ASC;
}

void UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_Targets(ATurpGameStateBase* GameState,
	FTurpAbilityTargetData TargetData)
{
	GameState->CombatPacket.Targets.Add(TargetData);
}

void UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_GameplayEffect(ATurpGameStateBase* GameState,
                                                                        TSubclassOf<UGameplayEffect> GE)
{
	GameState->CombatPacket.GameplayEffect = GE;
}

void UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_TargetHit(ATurpGameStateBase* GameState, bool Hit)
{
	GameState->CombatPacket.isHit.Add(Hit);
}

uint8 UTurpAbilitySystemBlueprintFL::DieRoll(int Count, int Type)
{
	int DieRollResult = 0;
	for (int i = 0; i < Count; ++i)
	{
		DieRollResult += UKismetMathLibrary::RandomInteger(Type) + 1;
	}
	return DieRollResult;
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffect(const ATurpGameStateBase* GameState,
	const FGameplayEffectParams& EffectParams)
{
	const auto SourceASC = GameState->CombatPacket.SourceASC;
	auto ContextHandle = SourceASC->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceASC);
	auto spec = SourceASC->MakeOutgoingSpec(EffectParams.EffectClass, 1, ContextHandle);
	spec.Data->SetSetByCallerMagnitude(EffectParams.AttributeTag, -UTurpAbilitySystemBlueprintFL::DieRoll(EffectParams.DieCount, EffectParams.DieType));
	
	// TODO: Change based on mutliple targets
	SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, GameState->CombatPacket.Targets[0].ASC);
}
