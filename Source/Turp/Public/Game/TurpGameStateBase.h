// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/ConditionInfo.h"
#include "AbilitySystem/TurpAbilityTypes.h"
#include "AbilitySystem/Data/EffectInfo.h"
#include "GameFramework/GameStateBase.h"
#include "TurpGameStateBase.generated.h"

class AEnemyCharacter;
class UAttributeSet;
class ATurpCharacter;
/**
 * 
 */
UCLASS()
class TURP_API ATurpGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void ResetCombatPacket();

	UPROPERTY(BlueprintReadWrite)
	FCombatPacket CombatPacket;

	// From Data Asset.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|AbilityInfo")
	TObjectPtr<UConditionInfo> GameplayConditionInformation;

	// From Data Asset.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|AbilityInfo")
	TObjectPtr<UEffectInfo> GameplayEffectInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|AbilityInfo")
	TSubclassOf<UGameplayEffect> DefaultDamageGameplayEffect;

	
};
