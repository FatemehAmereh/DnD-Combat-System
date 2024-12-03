// Copyright Erza.


#include "Character/TurpCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATurpCharacter::ATurpCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.0f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ATurpCharacter::SetDefaultAbilitySystemVariables(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = ASC;
	AttributeSet = AS;
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