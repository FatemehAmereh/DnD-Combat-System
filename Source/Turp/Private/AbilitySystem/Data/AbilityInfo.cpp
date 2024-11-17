// Copyright Erza.


#include "AbilitySystem/Data/AbilityInfo.h"

FTurpAbilityInfo UAbilityInfo::FindAbilityInfoByTag(const FGameplayTag& AbilityTag) const
{
	for (const FTurpAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	return FTurpAbilityInfo();
}
