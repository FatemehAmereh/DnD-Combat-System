// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TurpGameplayAbility.generated.h"

USTRUCT(BlueprintType)
struct FGameplayEffectParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> EffectClass;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 DieCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 DieType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag TagToBeGranted;
};

class ATurpGameStateBase;
/**
 * 
 */
UCLASS()
class TURP_API UTurpGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// Set the combat packet values: SourceASC and GameplayEffectClass
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable)
	void MakeEffect();
	
	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Effect Parameters")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Ability Settings|Effect Parameters")
	FGameplayEffectParams GameplayEffectParams;
	
	UPROPERTY(BlueprintReadOnly, Category="Native Variable")
	TObjectPtr<ATurpGameStateBase> TurpGameState;
};
