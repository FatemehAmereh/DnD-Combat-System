// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Game/TurpGameStateBase.h"
#include "TurpGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UTurpGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FGameplayTag GetAbilityTag() const;
	
protected:
	// Set the combat packet values: SourceASC and GameplayEffectClass
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;

	// Face the ability owner towards the target before starting attack initiates.
	UFUNCTION(BlueprintCallable)
	virtual void FaceTargetBeforeAttacking(const FVector TargetPoint);

	UFUNCTION(BlueprintCallable)
	void TraceToFindTargets(const FVector TraceCenter, bool ApplyEffect = true);
	
	// Return the first target in the current combat packet.
	virtual FVector FindTargetToFaceTowards();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability Settings")
	FGameplayAbilityProperties GameplayAbilityProperties;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATurpGameStateBase> TurpGameState;

	// Used in blueprint.
	UPROPERTY(BlueprintReadWrite, Category="Target")
	int TargetsReceived = 0;
};
