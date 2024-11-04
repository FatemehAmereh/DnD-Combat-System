// Copyright Erza.


#include "Character\TurpCharacterBase.h"

ATurpCharacterBase::ATurpCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATurpCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurpCharacterBase::InitAbilityActorInfo()
{
}
