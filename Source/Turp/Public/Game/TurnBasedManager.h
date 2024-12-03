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
	TObjectPtr<ATurpCharacterBase> Character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AS;
};

UCLASS()
class TURP_API ATurnBasedManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurnBasedManager();
	UAbilitySystemComponent* GetActivePartyMembersAbilitySystemComponent() const;
	
	int32 ActivePartyMemberIndex = 0;
	
	// Character and Enemy Data.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	int32 PartyCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	TSubclassOf<ATurpCharacter> PartyCharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Assets|Characters")
	int32 EnemyCount = 1;

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
};
