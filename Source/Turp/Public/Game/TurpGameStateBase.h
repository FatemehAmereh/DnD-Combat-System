// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameStateBase.h"
#include "TurpGameStateBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDice
{
	GENERATED_BODY()

	void Reset()
	{
		Count = 0;
		Type = 0;
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 Count;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 Type;
};

USTRUCT(BlueprintType)
struct FTurpAbilityTargetData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(BlueprintReadWrite)
	FVector Location;
};

USTRUCT(BlueprintType)
struct FAbilityDamageProperties
{
	GENERATED_BODY()

	void Reset()
	{
		NeedsSavingThrow = false;
		TakeHalfDamageOnSuccess = false;
		SavingThrowTag = FGameplayTag::EmptyTag;
		ModifierTag =FGameplayTag::EmptyTag;
		Dice = FDice();
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool NeedsSavingThrow;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool TakeHalfDamageOnSuccess;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag SavingThrowTag;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FDice Dice;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag ModifierTag;
};

USTRUCT(BlueprintType)
struct FAbilityConditionProperties
{
	GENERATED_BODY()

	void Reset()
	{
		NeedsSavingThrow = false;
		SavingThrowTag = FGameplayTag::EmptyTag;
		TagsToGrant.Empty();
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool NeedsSavingThrow;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag SavingThrowTag;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FGameplayTag> TagsToGrant;
};

USTRUCT(BlueprintType)
struct FOtherAbilityProperties
{
	GENERATED_BODY()

	void Reset()
	{
		ModifierMagnitude = 0;
		ModifierTag = FGameplayTag::EmptyTag;
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ModifierMagnitude;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag ModifierTag;
};

USTRUCT(BlueprintType)
struct FGameplayAbilityProperties
{
	GENERATED_BODY()

	void Reset()
	{
		EffectClass = nullptr;
		TargetCount = 0;
		Range = 0;
		Damage.Reset();
		Condition.Reset();
		OtherAttributeChanges.Reset();
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int TargetCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Range;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityDamageProperties Damage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityConditionProperties Condition;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FOtherAbilityProperties OtherAttributeChanges;
};

USTRUCT(Blueprintable, BlueprintType)
struct FCombatPacket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTurpAbilityTargetData> Targets;

	UPROPERTY(BlueprintReadWrite)
	FGameplayAbilityProperties AbilityProperties;
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
