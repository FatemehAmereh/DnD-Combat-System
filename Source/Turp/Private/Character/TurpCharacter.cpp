// Copyright Erza.


#include "Character/TurpCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ATurpCharacter::ATurpCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTurpAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UTurpAttributeSet>("AttributeSet");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.0f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ATurpCharacter::SetDefaultProperties(const FCharacterClassData CharacterClassInformation)
{
	//AbilitySystemComponent = ASC;
	DefaultPrimaryAttributesEffect = CharacterClassInformation.DefaultPrimaryAttributesEffect;
	StartUpGameplayAbilities = CharacterClassInformation.StartUpGameplayAbilities;
	CharacterClass = CharacterClassInformation.CharacterClass;
}

void ATurpCharacter::SetAbilitySystemComponentOwnerActor(AActor* ASCOwner)
{
	AbilitySystemComponentOwner = ASCOwner;
}

// int32 ATurpCharacter::GetPlayerLevel_Implementation()
// {
// 	const auto TurpPlayerState = GetPlayerState<ATurpPlayerState>();
// 	return TurpPlayerState->GetPlayerLevel(PartyIndex);
// }

void ATurpCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//InitAbilityActorInfo();
}

void ATurpCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(AbilitySystemComponentOwner, this);
	InitializeDefaultAttributes();
	InitializeStartupAbilities();
}