// Copyright Erza.


#include "AbilitySystem\Data\ConditionInfo.h"

bool UConditionInfo::FindConditionInfoWithTag(const FGameplayTag ConditionTag, TArray<FActionStatusData>& ActionsArray)
{
	for (const FConditionInfoData& ConditionInfo : ConditionInformation)
	{
		if(ConditionInfo.ConditionTag.MatchesTagExact(ConditionTag))
		{
			ActionsArray = ConditionInfo.Actions;
			return true;
		}
	}
	return false;
}
