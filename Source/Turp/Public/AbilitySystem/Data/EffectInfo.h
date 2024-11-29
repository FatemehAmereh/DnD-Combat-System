// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TurpAbilityTypes.h"
#include "Engine/DataAsset.h"
#include "EffectInfo.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class TURP_API UEffectInfo : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Information")
	TMap<FGameplayTag, FGameplayEffectProperties> EffectInformation;

public:
	FGameplayEffectProperties* GetEffectInfoWithTag(const FGameplayTag& EffectTag);
};
