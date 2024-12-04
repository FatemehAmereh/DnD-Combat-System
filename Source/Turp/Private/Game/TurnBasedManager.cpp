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

	// Party Ability System Initialization:
	//   Creating Ability System Components and Attribute Sets for Party Characters.
	for (int i = 0; i < PartyCount; ++i)
	{
		FCharacterInfo CharacterInfo;
		const auto ASC = CreateDefaultSubobject<UTurpAbilitySystemComponent>(
			*FString::Printf(TEXT("AbilitySystemComponent%d"), i));
		ASC->SetIsReplicated(true);
		ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		CharacterInfo.ASC = ASC;
		ASCs.Add(ASC);
		
		const auto AS = CreateDefaultSubobject<UTurpAttributeSet>(
			*FString::Printf(TEXT("AttributeSet%d"), i));
		CharacterInfo.AS = AS;

		PartyMembers.Add(CharacterInfo);
	}
}

void ATurnBasedManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Create Party Characters.
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
	
		// Roll Initiative.
		// TODO: Use the UTurpAbilitySystemBlueprintFL::MakeActionCheck To roll.
		PartyMembers[i].Initiative =
				UTurpAbilitySystemBlueprintFL::RollDie(1, 20) +
				Cast<UTurpAttributeSet>(PartyMembers[i].AS)->GetDexterityMod();
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
}

void ATurnBasedManager::PossessNewCharacter()
{
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
