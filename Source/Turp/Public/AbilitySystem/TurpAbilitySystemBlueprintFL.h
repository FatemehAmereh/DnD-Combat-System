// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/TurpGameplayAbility.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TurpAbilitySystemBlueprintFL.generated.h"

class UTurpAttributeSet;
struct FGameplayAbilityProperties;
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
	/// UI
	UFUNCTION(BlueprintPure, Category="TurpAbilitySystemBlueprintFunctionLibrary|WidgetController" )
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	///
	
	/// Combat Packet Update.
	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void SetSourceASCForCombatPacket(ATurpGameStateBase* GameState, UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddTargetForCombatPacket(ATurpGameStateBase* GameState, FTurpAbilityTargetData TargetData);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddTargetASCForCombatPacket(ATurpGameStateBase* GameState, UAbilitySystemComponent* TargetASC);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void AddTargetLocationForCombatPacket(ATurpGameStateBase* GameState, FVector TargetLocation);
	
	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void SetGameplayAbilityPropertiesForCombatPacket(ATurpGameStateBase* GameState, const FGameplayAbilityProperties& AbilityProperties);
	///
	
	/// Gameplay Effect
	static void ApplyGameplayEffectToTarget(const ATurpGameStateBase* GameState, const uint8 TargetIndex);

	UFUNCTION(BlueprintCallable, Category="TurpAbilitySystemBlueprintFunctionLibrary|CombatPacket" )
	static void ApplyGameplayEffectToAllTargets(const ATurpGameStateBase* GameState);
	///

	/// Utility
	static uint8 RollDie(int Count, int Type);
	static constexpr float FootToCentimeter(const int Foot)
	{
		return Foot / 3.281f * 100.f;
	}
	///

private:
	// Return true if target succeeds the saving throw.
	static bool MakeSavingThrow(const FGameplayTag& SavingThrowTag, const UTurpAttributeSet& SourceAS, const UTurpAttributeSet& TargetAS, FString& DebugMsg);
	static float GetSavingThrowModifier(const UTurpAttributeSet& AttributeSet, const FGameplayTag& SavingThrowTag);

	// Return true if target is Hit by the attack.
	static bool MakeAttackRoll(const UTurpAttributeSet& SourceAS, const UTurpAttributeSet& TargetAS, FString& DebugMsg);
};
