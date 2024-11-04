// Copyright Erza.


#include "Character/TurpCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/TurpPlayerState.h"

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

void ATurpCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ATurpCharacter::InitAbilityActorInfo()
{
	const auto TurpPlayerState = GetPlayerState<ATurpPlayerState>();
	check(TurpPlayerState);
	
	AttributeSet = TurpPlayerState->GetAttributeSet();
	AbilitySystemComponent = TurpPlayerState->GetAbilitySystemComponent();

	// This will automatically register the attribute set with the ability system on this actor.
	AbilitySystemComponent->InitAbilityActorInfo(TurpPlayerState, this);

	InitializeDefaultAttributes();
}
