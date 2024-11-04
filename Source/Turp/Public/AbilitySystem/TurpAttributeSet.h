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
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Constitution);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Wisdom);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Charisma);

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ArmorClass);
	
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData ProficiencyBonus;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, ProficiencyBonus);
//

// Secondary Attributs
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData Initiative;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Initiative);
//

// Vital Attributes
	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTurpAttributeSet, MaxHealth);
//
};
