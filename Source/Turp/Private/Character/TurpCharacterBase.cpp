// Copyright Erza.


#include "Character\TurpCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

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

void ATurpCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(AbilitySystemComponent));
	check(GameplayEffectClass);

	auto ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	// TODO: what is this level exactly
	auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ATurpCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultModAttributes, 1.f);
	//ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}
