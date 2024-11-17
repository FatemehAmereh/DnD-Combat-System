// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

//////// Not sure if I would need this!

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FTurpAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class TURP_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInformation")
	TArray<FTurpAbilityInfo> AbilityInformation;

	FTurpAbilityInfo FindAbilityInfoByTag(const FGameplayTag& AbilityTag) const;
};
