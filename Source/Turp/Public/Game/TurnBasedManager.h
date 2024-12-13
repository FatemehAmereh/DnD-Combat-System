// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnBasedManager.generated.h"

class ATurpCharacterBase;
class UAttributeSet;
class UAbilitySystemComponent;
class AEnemyCharacter;
class ATurpCharacter;

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ATurpCharacterBase> Character = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Initiative = 0;
};

UCLASS()
class TURP_API ATurnBasedManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurnBasedManager();
	void EndTurn();
	UAbilitySystemComponent* GetActivePartyMembersAbilitySystemComponent() const;
	
	// Character and Enemy Data.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Assets|Characters")
	int32 PartyCount = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	TSubclassOf<ATurpCharacter> PartyCharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	int32 EnemyCount = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	TSubclassOf<AEnemyCharacter> EnemyCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Assets|Spawn Locations")
	TObjectPtr<AActor> PartySpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Assets|Spawn Locations")
	TObjectPtr<AActor> EnemySpawnLocation;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FCharacterInfo> PartyMembers;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ATurpCharacterBase>> Enemies;
	
	virtual void BeginPlay() override;
	
private:
	int32 ActivePartyMemberIndex = 0;
	void PossessNewCharacter();
	void SetUIReference();
};
