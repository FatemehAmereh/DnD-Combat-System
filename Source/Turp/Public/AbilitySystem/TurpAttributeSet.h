// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TurpAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class TURP_API UTurpAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
// Primary Attributes
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Constitution);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Wisdom);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Charisma);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ArmorClass);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData ProficiencyBonus;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ProficiencyBonus);	
//

// Modifiers
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData StrengthMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, StrengthMod);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData DexterityMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, DexterityMod);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData ConstitutionMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ConstitutionMod);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData IntelligenceMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, IntelligenceMod);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData WisdomMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, WisdomMod);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData CharismaMod;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, CharismaMod);
//

// Saving Throws
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData StrengthST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, StrengthST);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData DexterityST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, DexterityST);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData ConstitutionST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ConstitutionST);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData IntelligenceST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, IntelligenceST);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData WisdomST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, WisdomST);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData CharismaST;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, CharismaST);
	//
	
// Secondary Attributes
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Secondary")
	FGameplayAttributeData Initiative;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Initiative);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Secondary")
	FGameplayAttributeData SpellSaveDC;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, SpellSaveDC);
//

// Vital Attributes
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, MaxHealth);
//
};
