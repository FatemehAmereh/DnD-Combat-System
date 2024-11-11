// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Character/TurpCharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API AEnemyCharacter : public ATurpCharacterBase
{
	GENERATED_BODY()
	
	AEnemyCharacter();

public:
	int32 GetPlayerLevel();
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
