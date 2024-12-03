// Copyright Erza.


#include "Game/TurnBasedManager.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Character/EnemyCharacter.h"
#include "Character/TurpCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/TurpHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"

ATurnBasedManager::ATurnBasedManager()
{
	PrimaryActorTick.bCanEverTick = false;

	// Party Ability System Initialization.
	for (int i = 0; i < PartyCount; ++i)
	{
		FCharacterInfo CharacterInfo;
		const auto ASC = CreateDefaultSubobject<UTurpAbilitySystemComponent>(
			*FString::Printf(TEXT("AbilitySystemComponent%d"), i));
		ASC->SetIsReplicated(true);
		ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		CharacterInfo.ASC = ASC;
            
		const auto AS = CreateDefaultSubobject<UTurpAttributeSet>(
			*FString::Printf(TEXT("AttributeSet%d"), i));
		CharacterInfo.AS = AS;

		PartyMembers.Add(CharacterInfo);
	}
}

UAbilitySystemComponent* ATurnBasedManager::GetActivePartyMembersAbilitySystemComponent() const
{
	return PartyMembers[ActivePartyMemberIndex].ASC;
}

void ATurnBasedManager::BeginPlay()
{
	Super::BeginPlay();

	// Party Initialization.
	for (int i = 0; i < PartyCount; ++i)
	{
		const auto PartyMember = GetWorld()->SpawnActorDeferred<ATurpCharacter>(
			PartyCharacterClass,
			PartySpawnLocation->GetTransform(),
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//PartyMember->SetPartyIndex(i);
		PartyMember->SetAbilitySystemComponentOwnerActor(this);
		PartyMember->SetDefaultAbilitySystemVariables(PartyMembers[i].ASC, PartyMembers[i].AS);
		PartyMember->FinishSpawning(PartySpawnLocation->GetTransform());
		PartyMembers[i].Character = PartyMember;
	}

	// Enemy Initialization.
	for (int i = 0; i < EnemyCount; ++i)
	{
		const auto Enemy = GetWorld()->SpawnActorDeferred<AEnemyCharacter>(
			EnemyCharacterClass,
			EnemySpawnLocation->GetTransform(),
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Enemy->FinishSpawning(EnemySpawnLocation->GetTransform());
		Enemies.Add(Enemy);
	}

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->Possess(PartyMembers[ActivePartyMemberIndex].Character);
	const auto OverlayWidgetController = PlayerController->GetHUD<ATurpHUD>()->GetOverlayWidgetController();
	OverlayWidgetController->SetTurnBasedManager(this);
}
//
// UAbilitySystemComponent* ATurnBasedManager::GetAbilitySystemComponentWithIndex(const int32 PartyMemberIndex) const
// {
// 	return PartyAbilitySystemComponents[PartyMemberIndex];
// }
//
// UAttributeSet* ATurnBasedManager::GetAttributeSet(const int32 PartyMemberIndex) const
// {
// 	return PartyAttributeSets[PartyMemberIndex];
// }