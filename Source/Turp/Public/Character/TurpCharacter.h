// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void PossessedBy(AController* NewController) override;
	
private:
	void InitAbilityActorInfo() override;
};
