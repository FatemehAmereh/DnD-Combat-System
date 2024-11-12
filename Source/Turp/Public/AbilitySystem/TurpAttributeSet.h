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
public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Dexterity);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Constitution);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Wisdom);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Charisma);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ArmorClass);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ProficiencyBonus);

	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, StrengthMod);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, DexterityMod);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ConstitutionMod);	
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, IntelligenceMod);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, WisdomMod);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, CharismaMod);

	
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, StrengthST);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, DexterityST);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ConstitutionST);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, IntelligenceST);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, WisdomST);
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, CharismaST);
	
protected:
// Primary Attributes
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Strength;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Dexterity;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Constitution;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Intelligence;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Wisdom;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData Charisma;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData ArmorClass;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Primary")
	FGameplayAttributeData ProficiencyBonus;
//

// Modifiers
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData StrengthMod;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData DexterityMod;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData ConstitutionMod;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData IntelligenceMod;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData WisdomMod;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Modifier")
	FGameplayAttributeData CharismaMod;
//

// Saving Throws
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData StrengthST;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData DexterityST;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData ConstitutionST;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData IntelligenceST;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData WisdomST;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Saving Throw")
	FGameplayAttributeData CharismaST;
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
