// Copyright Erza.


#include "AbilitySystem/Data/AbilityIconInfo.h"

FAbilityIconData UAbilityIconInfo::GetAbilityIconInfoWithTag(const FGameplayTag& Tag)
{
	if(const auto AbilityData = AbilityIconInformation.Find(Tag))
	{
		return *AbilityData;
	}
	
	return FAbilityIconData{};
}
