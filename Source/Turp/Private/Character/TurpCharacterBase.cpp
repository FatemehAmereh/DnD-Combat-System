// Copyright Erza.


#include "Character\TurpCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"

ATurpCharacterBase::ATurpCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ATurpCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector ATurpCharacterBase::GetCombatSocketLocation_Implementation()
{
	return GetMesh()->GetSocketLocation("AttackSocket");
}

float ATurpCharacterBase::GetClassSpecificAttackRollModifier() const
{
	const auto AS = Cast<UTurpAttributeSet>(AbilitySystemComponent->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	if(CharacterClass == ECharacterClassTypes::Wizard)
	{
		return Cast<UTurpAttributeSet>(AS)->GetIntelligenceMod();
	}
	if(CharacterClass == ECharacterClassTypes::Cleric)
	{
		return Cast<UTurpAttributeSet>(AS)->GetWisdomMod();
	}
	if(CharacterClass == ECharacterClassTypes::Fighter)
	{
		// Should be either Strength or Dexterity based on weapon equipped.
		return Cast<UTurpAttributeSet>(AS)->GetStrengthMod();
	}
	
	return 0;
}

// void ATurpCharacterBase::SetPartyIndex(const int32 Index)
// {
// 	PartyIndex = Index;
// }

void ATurpCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
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
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());;
}

void ATurpCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributesEffect, 1.f);
	Cast<UTurpAbilitySystemComponent>(AbilitySystemComponent)->InitializeConditionActions();
}

void ATurpCharacterBase::InitializeStartupAbilities() const
{
	// TODO: has to initialize all abilities later
	
	const auto TurpAbilitySystemComponent = CastChecked<UTurpAbilitySystemComponent>(AbilitySystemComponent);
	for (const auto& AbilityClass : StartUpGameplayAbilities)
	{
		TurpAbilitySystemComponent->AddCharacterAbility(AbilityClass);	
	}
}
