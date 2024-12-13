// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Character/TurpCharacterBase.h"
#include "TurpCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API ATurpCharacter : public ATurpCharacterBase
{
	GENERATED_BODY()

public:
	ATurpCharacter();
	void SetDefaultProperties(const FCharacterClassData CharacterClassInformation);
	void SetAbilitySystemComponentOwnerActor(AActor* ASCOwner);
	// virtual int32 GetPlayerLevel_Implementation() override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY()
	TObjectPtr<AActor> AbilitySystemComponentOwner;
};
