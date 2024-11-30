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

FActionStatusData* UConditionInfo::GetActionStatus(const FGameplayTag ConditionTag, const EActionEnum Action)
{
	if(const auto ConditionInfo = ConditionInformation.Find(ConditionTag))
	{
		return ConditionInfo->Actions.Find(Action);
	}
	return nullptr;
}
