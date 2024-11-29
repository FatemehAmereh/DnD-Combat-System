// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/ConditionInfo.h"
#include "AbilitySystem/TurpAbilityTypes.h"
#include "AbilitySystem/Data/EffectInfo.h"
#include "GameFramework/GameStateBase.h"
#include "TurpGameStateBase.generated.h"



/**
 * 
 */
UCLASS()
class TURP_API ATurpGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ResetCombatPacket();

	UPROPERTY(BlueprintReadWrite)
	FCombatPacket CombatPacket;

	// From Data Asset.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets")
	TObjectPtr<UConditionInfo> GameplayConditionInformation;

	// From Data Asset.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets")
	TObjectPtr<UEffectInfo> GameplayEffectInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets")
	TSubclassOf<UGameplayEffect> DefaultDamageGameplayEffect;
};
