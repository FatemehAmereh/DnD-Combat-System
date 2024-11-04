// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurpCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

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

private:
	virtual void InitAbilityActorInfo();
};
