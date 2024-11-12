// Copyright Erza.


#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void UTurpGameplayAbility::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

	TurpGameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	TurpGameState->ResetCombatPacket();
	UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_GameplayEffect(TurpGameState, GameplayEffectClass);
}
