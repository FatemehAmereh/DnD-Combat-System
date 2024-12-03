// Copyright Erza.


#include "Player\TurpPlayerState.h"

#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Engine/GameEngine.h"

// ATurpPlayerState::ATurpPlayerState()
// {
// 	if(const auto GameInstance = Cast<UGameEngine>(GEngine)->GameInstance)
// 	{
// 		if(const auto TurnBasedManager = GameInstance->GetSubsystem<UTurnBasedManager>())
//         {
//         	for (int i = 0; i < TurnBasedManager->GetPartyCount(); ++i)
//             {
//                 auto ASC = CreateDefaultSubobject<UTurpAbilitySystemComponent>(
//                 	*FString::Printf(TEXT("AbilitySystemComponent%d"), i));
//                 ASC->SetIsReplicated(true);
//                 ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full);
//                 AbilitySystemComponents.Add(ASC);
//             
//                 auto AS = CreateDefaultSubobject<UTurpAttributeSet>(
//                 	*FString::Printf(TEXT("AttributeSet%d"), i));
//                 AttributeSets.Add(AS);
//             }
//         }
// 	}
// 	
// }
//
// UAbilitySystemComponent* ATurpPlayerState::GetAbilitySystemComponentWithIndex(const int32 PartyMemberIndex) const
// {
// 	return AbilitySystemComponents[PartyMemberIndex];
// }
//
// UAttributeSet* ATurpPlayerState::GetAttributeSet(const int32 PartyMemberIndex) const
// {
// 	return AttributeSets[PartyMemberIndex];
// }
//
// int32 ATurpPlayerState::GetPlayerLevel(const int32 PartyMemberIndex) const
// {
// 	return Levels[PartyMemberIndex];
// }
