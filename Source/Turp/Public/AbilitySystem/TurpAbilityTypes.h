// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TurpAbilityTypes.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EAoeType : uint8
{
	None, Box, Sphere, Cone
};

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
	int Count;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Type;
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
		DoesDamage = false;
		TakeHalfDamageOnSuccess = false;
		ApplyDamageEveryTurn = false;
		SavingThrowTag = FGameplayTag::EmptyTag;
		Dice = FDice();
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool DoesDamage = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool TakeHalfDamageOnSuccess;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool ApplyDamageEveryTurn = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag SavingThrowTag;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FDice Dice;
};

USTRUCT(BlueprintType)
struct FAbilityConditionProperties
{
	GENERATED_BODY()

	void Reset()
	{
		SavingThrowTag = FGameplayTag::EmptyTag;
		TagsToGrant.Empty();
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag SavingThrowTag;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FGameplayTag> TagsToGrant;
};

USTRUCT(BlueprintType)
struct FGameplayAbilityProperties
{
	GENERATED_BODY()

	void Reset()
	{
		AbilityTag = FGameplayTag::EmptyTag;
		TargetCount = 0;
		Range = 0;
		AoeType = EAoeType::None;
		AoeRange = 0;
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag AbilityTag;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 TargetCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 Range;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EAoeType AoeType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 AoeRange;
};

USTRUCT(BlueprintType)
struct FGameplayEffectProperties
{
	GENERATED_BODY()

	void Reset()
	{
		Duration = 0;
		CanStack = false;
		Damage.Reset();
		Condition.Reset();
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 Duration;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool CanStack = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityDamageProperties Damage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityConditionProperties Condition;
};

USTRUCT(BlueprintType)
struct FCombatPacket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTurpAbilityTargetData> Targets;

	UPROPERTY(BlueprintReadWrite)
	FGameplayAbilityProperties AbilityProperties;

	UPROPERTY(BlueprintReadWrite)
	FGameplayEffectProperties EffectProperties;
};

USTRUCT(BlueprintType)
struct FEffectStackElement
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 DurationLeft;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 StackCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 DamageSaveDC = 0;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool ConditionGranted = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 ConditionSpellSaveDC = 0;
};