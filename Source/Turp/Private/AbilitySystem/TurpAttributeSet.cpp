// Copyright Erza.


#include "AbilitySystem/TurpAttributeSet.h"

#include "GameplayEffectExtension.h"

namespace
{
	float CalculateAttributeModifier(float AttributeValue)
	{
		return FMath::Floor((AttributeValue-10.f) / 2.f);
	}
}

void UTurpAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Tailoring for wizard right now.
	if(Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetStrength());
		SetStrengthMod(NewModifier);
		SetStrengthST(NewModifier);
	}
	else if(Data.EvaluatedData.Attribute == GetDexterityAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetDexterity());
		SetDexterityMod(NewModifier);
		SetDexterityST(NewModifier);
		SetInitiative(NewModifier);
		SetArmorClass(10.f + NewModifier);
	}
	else if(Data.EvaluatedData.Attribute == GetConstitutionAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetConstitution());
		SetConstitutionMod(NewModifier);
		SetConstitutionST(NewModifier);
		const float NewMaxHealth = 6.f + NewModifier; 
		SetMaxHealth(NewMaxHealth);
		SetHealth(NewMaxHealth);
	}
	else if(Data.EvaluatedData.Attribute == GetIntelligenceAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetIntelligence());
		SetIntelligenceMod(NewModifier);
		SetIntelligenceST(NewModifier);
		SetSpellSaveDC(8.f + NewModifier + GetProficiencyBonus());
	}
	else if(Data.EvaluatedData.Attribute == GetWisdomAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetWisdom());
		SetWisdomMod(NewModifier);
		SetWisdomST(NewModifier);
	}
	else if(Data.EvaluatedData.Attribute == GetCharismaAttribute())
	{
		const float NewModifier = CalculateAttributeModifier(GetCharisma());
		SetCharismaMod(NewModifier);
		SetCharismaST(NewModifier);
	}
	else if(Data.EvaluatedData.Attribute == GetProficiencyBonusAttribute())
	{
		SetSpellSaveDC(8.f + GetIntelligenceMod() + GetProficiencyBonus());
	}
}
