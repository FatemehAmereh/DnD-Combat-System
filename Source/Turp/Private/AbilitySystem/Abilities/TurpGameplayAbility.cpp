// Copyright Erza.


#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "Game/TurpGameStateBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UTurpGameplayAbility::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

	TurpGameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	TurpGameState->ResetCombatPacket();
	UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_GameplayEffect(TurpGameState, GameplayEffectClass);
	UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_SourceASC(TurpGameState, GetAbilitySystemComponentFromActorInfo());
	
	GameplayEffectParams.EffectClass = GameplayEffectClass;
}

// void UTurpGameplayAbility::FaceTargetBeforeAttacking()
// {
// 	Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->Execute_FaceTarget(GetAvatarActorFromActorInfo(),);
// }
