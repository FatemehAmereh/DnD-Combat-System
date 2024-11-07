// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurpCharacterBase.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class TURP_API ATurpCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATurpCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<UGameplayAbility> StartUpGameplayAbility;
	
	void InitializeDefaultAttributes() const;
	void InitializeStartupAbilities(const TSubclassOf<UGameplayAbility> AbilityClass) const;
private:
	virtual void InitAbilityActorInfo();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
};
