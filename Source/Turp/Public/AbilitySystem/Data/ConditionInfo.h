// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/TurpAbilityTypes.h"
#include "Engine/DataAsset.h"
#include "ConditionInfo.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum class EActionStatus
{
	Advantage, Disadvantage, AutoSave, AutoFail, Modifier
};

USTRUCT(BlueprintType)
struct FActionStatusData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ActionTag;
	
	UPROPERTY(EditDefaultsOnly)
	EActionStatus StatusEnum;

	UPROPERTY(EditDefaultsOnly)
	FDice ModifierDice;
};

USTRUCT(BlueprintType)
struct FConditionInfoData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ConditionTag;

	UPROPERTY(EditDefaultsOnly)
	TArray<FActionStatusData> Actions;
};

/**
 * 
 */
UCLASS()
class TURP_API UConditionInfo : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ConditionInformation")
	TArray<FConditionInfoData> ConditionInformation;

public:
	 bool FindConditionInfoWithTag(const FGameplayTag ConditionTag, TArray<FActionStatusData>& ActionsArray);
};
