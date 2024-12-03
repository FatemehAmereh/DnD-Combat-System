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
	//virtual int32 GetPlayerLevel_Implementation() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
