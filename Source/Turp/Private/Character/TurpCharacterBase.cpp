// Copyright Erza.


#include "Character\TurpCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"

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
	ApplyEffectToSelf(DefaultPrimaryAttributesEffect, 1.f);
}

void ATurpCharacterBase::InitializeStartupAbilities(const TSubclassOf<UGameplayAbility> AbilityClass) const
{
	// TODO: has to initialize all abilities later
	
	const auto TurpAbilitySystemComponent = CastChecked<UTurpAbilitySystemComponent>(AbilitySystemComponent);
	TurpAbilitySystemComponent->AddCharacterAbility(AbilityClass);
}
