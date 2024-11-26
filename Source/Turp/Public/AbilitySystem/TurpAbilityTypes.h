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
		AoeType = EAoeType::None;
		AoeRange = 0;
	}
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int TargetCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Range;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EAoeType AoeType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int AoeRange;
};

USTRUCT(BlueprintType)
struct FGameplayEffectProperties
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityDamageProperties Damage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAbilityConditionProperties Condition;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FOtherAbilityProperties OtherAttributeChanges;
	
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
};