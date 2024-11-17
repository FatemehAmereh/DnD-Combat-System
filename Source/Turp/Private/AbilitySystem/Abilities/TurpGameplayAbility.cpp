// Copyright Erza.


#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/Tasks/TargetDataUnderMouse.h"
#include "Game/TurpGameStateBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

FGameplayTag UTurpGameplayAbility::GetAbilityTag() const
{
	return AbilityTag;
}

void UTurpGameplayAbility::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	
	TargetsReceived = 0;
	TurpGameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	TurpGameState->ResetCombatPacket();
	UTurpAbilitySystemBlueprintFL::SetSourceASCForCombatPacket(TurpGameState, GetAbilitySystemComponentFromActorInfo());
	UTurpAbilitySystemBlueprintFL::SetGameplayAbilityPropertiesForCombatPacket(TurpGameState, GameplayAbilityProperties);
}

void UTurpGameplayAbility::FaceTargetBeforeAttacking()
{
	Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->Execute_FaceTarget(GetAvatarActorFromActorInfo(), FindTargetToFaceTowards());
}


FVector UTurpGameplayAbility::FindTargetToFaceTowards()
{
	if(!TurpGameState->CombatPacket.Targets.IsEmpty())
	{
		if(TurpGameState->CombatPacket.Targets[0].ASC)
		{
			return TurpGameState->CombatPacket.Targets[0].ASC->GetAvatarActor()->GetActorLocation();
		}
		else
		{
			return TurpGameState->CombatPacket.Targets[0].Location;
		}
	}
	return FVector::Zero();
}
