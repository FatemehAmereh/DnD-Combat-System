// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/ConditionInfo.h"
#include "AbilitySystem/TurpAbilityTypes.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UConditionInfo> GameplayConditionDataAsset;
};
