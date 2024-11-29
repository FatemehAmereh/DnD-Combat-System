// Copyright Erza.


#include "AbilitySystem/Data/EffectInfo.h"

FGameplayEffectProperties* UEffectInfo::GetEffectInfoWithTag(const FGameplayTag& EffectTag)
{
	return EffectInformation.Find(EffectTag);
}
