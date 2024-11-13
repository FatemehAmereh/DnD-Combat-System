// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/TurpGameplayAbility.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TurpAbilitySystemBlueprintFL.generated.h"

struct FGameplayEffectParams;
class UGameplayEffect;
class UAbilitySystemComponent;
class ATurpGameStateBase;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class TURP_API UTurpAbilitySystemBlueprintFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UI
	UFUNCTION(BlueprintPure, Category="TurpAbilitySystemBlueprintFunctionLibrary|WidgetController" )
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	//
	
	// Combat Packet
	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void SetCombatPacketParam_SourceASC(ATurpGameStateBase* GameState, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddCombatPacketParam_Targets(ATurpGameStateBase* GameState, FTurpAbilityTargetData TargetData);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void SetCombatPacketParam_GameplayEffect(ATurpGameStateBase* GameState, TSubclassOf<UGameplayEffect> GE);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddCombatPacketParam_TargetHit(ATurpGameStateBase* GameState, bool Hit);
	//

	// Die Roll
	static uint8 DieRoll(int Count, int Type);
	//

	// Gameplay Effect
	static void ApplyGameplayEffect(const ATurpGameStateBase* GameState, const FGameplayEffectParams& EffectParams);
	//
};
