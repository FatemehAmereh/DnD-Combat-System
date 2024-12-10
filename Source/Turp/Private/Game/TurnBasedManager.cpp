// Copyright Erza.


#include "Game/TurnBasedManager.h"

#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
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
}

void ATurnBasedManager::BeginPlay()
{
	Super::BeginPlay();

	// Party Initialization.
	PartyMembers.Empty();
	for (int i = 0; i < PartyCount; ++i)
	{
		// Create Ability System Components and Attribute Sets.
		FCharacterInfo CharacterInfo;
		const auto ASC = NewObject<UTurpAbilitySystemComponent>(this, UTurpAbilitySystemComponent::StaticClass());
		ASC->SetIsReplicated(true);
		ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		ASC->RegisterComponent();
		CharacterInfo.ASC = ASC;

		CharacterInfo.AS = NewObject<UTurpAttributeSet>(this, UTurpAttributeSet::StaticClass());

		FTransform SpawnTransform = PartySpawnLocation->GetTransform();
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector(0, i * 100, 0));
		// Create Characters.
		const auto PartyMember = GetWorld()->SpawnActorDeferred<ATurpCharacter>(
			PartyCharacterClass,
			SpawnTransform,
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//PartyMember->SetPartyIndex(i);
		PartyMember->SetAbilitySystemComponentOwnerActor(this);
		PartyMember->SetDefaultAbilitySystemVariables(CharacterInfo.ASC, CharacterInfo.AS);
		PartyMember->FinishSpawning(SpawnTransform);
		CharacterInfo.Character = PartyMember;
	
		// Roll Initiative.
		// TODO: Use the UTurpAbilitySystemBlueprintFL::MakeActionCheck To roll.
		CharacterInfo.Initiative =
				UTurpAbilitySystemBlueprintFL::RollDie(1, 20) +
				Cast<UTurpAttributeSet>(CharacterInfo.AS)->GetDexterityMod();

		PartyMembers.Add(CharacterInfo);
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
	
	PartyMembers.Sort([](const FCharacterInfo& A, const FCharacterInfo& B)
	{
		return A.Initiative < B.Initiative;
	});
	
	// Set Active Character.
	PossessNewCharacter();
	
	SetUIReference();
}

void ATurnBasedManager::ChangeTurn()
{
	ActivePartyMemberIndex++;
	
	// TODO: When AI works, have a queue of party and enemy characters and check the size of that.
	if(ActivePartyMemberIndex >= PartyMembers.Num())
	{
		ActivePartyMemberIndex = 0;
	}
	PossessNewCharacter();

	// TODO: Update active Effect and Tags list.
}

void ATurnBasedManager::PossessNewCharacter()
{
	// TODO: Fix the rotation issue.
	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->Possess(PartyMembers[ActivePartyMemberIndex].Character);
}

void ATurnBasedManager::SetUIReference()
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	const auto OverlayWidgetController = PlayerController->GetHUD<ATurpHUD>()->GetOverlayWidgetController();
	OverlayWidgetController->SetTurnBasedManager(this);
}

UAbilitySystemComponent* ATurnBasedManager::GetActivePartyMembersAbilitySystemComponent() const
{
	return PartyMembers[ActivePartyMemberIndex].ASC;
}
