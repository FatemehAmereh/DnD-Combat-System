// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Union.h"
#include "GameFramework/GameStateBase.h"
#include "TurpGameStateBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FTurpAbilityTargetData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(BlueprintReadWrite)
	FVector Location;
};

USTRUCT(Blueprintable, BlueprintType)
struct FCombatPacket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTurpAbilityTargetData> Targets;
	
	// UPROPERTY(BlueprintReadWrite)
	// TArray<TObjectPtr<UAbilitySystemComponent>> TargetASCs;
	//
	// UPROPERTY(BlueprintReadWrite)
	// TArray<FVector> TargetLocations;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GameplayEffect;

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> isHit;
};

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
};
