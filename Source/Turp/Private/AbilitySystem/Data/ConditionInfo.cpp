// Copyright Erza.


#include "AbilitySystem\Data\ConditionInfo.h"

bool UConditionInfo::GetConditionInfoWithTag(const FGameplayTag ConditionTag,
	TMap<EActionEnum, FActionStatusData>& Actions)
{
	if(const auto SearchResult = ConditionInformation.Find(ConditionTag))
	{
		Actions = SearchResult->Actions;
		return true;
	}
	return false;
}
