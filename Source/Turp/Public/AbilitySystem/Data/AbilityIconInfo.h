// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityIconInfo.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FAbilityIconData
{
	GENERATED_BODY()

	// Texture
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MultiLine="true"))
	FText Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPaperSprite> Image;
};

/**
 * 
 */
UCLASS()
class TURP_API UAbilityIconInfo : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Icon Information")
	TMap<FGameplayTag, FAbilityIconData> AbilityIconInformation;

public:
	UFUNCTION(BlueprintCallable)
	FAbilityIconData GetAbilityIconInfoWithTag(const FGameplayTag& Tag);
};
