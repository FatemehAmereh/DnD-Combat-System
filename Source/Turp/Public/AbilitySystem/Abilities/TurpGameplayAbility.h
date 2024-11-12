// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TurpGameplayAbility.generated.h"

class ATurpGameStateBase;
/**
 * 
 */
UCLASS()
class TURP_API UTurpGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
private:
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATurpGameStateBase> TurpGameState;
};
