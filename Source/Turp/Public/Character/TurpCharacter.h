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

	virtual int32 GetPlayerLevel_Implementation() override;
protected:
	virtual void PossessedBy(AController* NewController) override;
	
private:
	void InitAbilityActorInfo() override;
};
