// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/TurpAbilityTypes.h"
#include "Engine/DataAsset.h"
#include "ConditionInfo.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum class EActionEnum
{
	// TODO: Add AttributeModifiers as well.
	AtkRoll, StrST, DexST, ConST, IntST, WisST, ChaST, 
};
const TArray<EActionEnum> ConditionActionList{ EActionEnum::AtkRoll, EActionEnum::StrST, EActionEnum::DexST, EActionEnum::ConST,
												   EActionEnum::IntST, EActionEnum::WisST, EActionEnum::ChaST};

UENUM(BlueprintType)
enum class EStatusEnum
{
	Advantage, Disadvantage, AutoSave, AutoFail, Modifier
};
const TArray<EStatusEnum> ActionStatusList{EStatusEnum::Advantage, EStatusEnum::Disadvantage, EStatusEnum::AutoSave,
												 EStatusEnum::AutoFail, EStatusEnum::Modifier};

USTRUCT(BlueprintType)
struct FActionStatusData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	EStatusEnum StatusEnum;

	UPROPERTY(EditDefaultsOnly)
	FDice ModifierDice;
};

USTRUCT(BlueprintType)
struct FConditionInfoData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EActionEnum, FActionStatusData> Actions;
};

/**
 * 
 */
UCLASS()
class TURP_API UConditionInfo : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition Information")
	TMap<FGameplayTag, FConditionInfoData> ConditionInformation;
public:
	bool GetConditionInfoWithTag(const FGameplayTag ConditionTag, TMap<EActionEnum, FActionStatusData>& Actions);
	FActionStatusData* GetActionStatus(const FGameplayTag ConditionTag, const EActionEnum Action);
};
