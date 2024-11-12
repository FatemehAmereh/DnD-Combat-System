// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TurpAbilitySystemBlueprintFL.generated.h"

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
	static void AddCombatPacketParam_TargetASC(ATurpGameStateBase* GameState, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddCombatPacketParam_TargetLocation(ATurpGameStateBase* GameState, FVector Location);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void SetCombatPacketParam_GameplayEffect(ATurpGameStateBase* GameState, TSubclassOf<UGameplayEffect> GE);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddCombatPacketParam_TargetHit(ATurpGameStateBase* GameState, bool Hit);
	//

	// Dice Roll
	static uint8 DieRoll(int Count, int Type);
	//

	
};
