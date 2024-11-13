// Copyright Erza.


#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

#include "AbilitySystemComponent.h"
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
	UTurpAbilitySystemBlueprintFL::SetCombatPacketParam_SourceASC(TurpGameState, GetAbilitySystemComponentFromActorInfo());
	
	GameplayEffectParams.EffectClass = GameplayEffectClass;
}

void UTurpGameplayAbility::MakeEffect()
{
	auto ContextHandle = TurpGameState->CombatPacket.SourceASC->MakeEffectContext();
	ContextHandle.AddSourceObject(TurpGameState->CombatPacket.SourceASC);
	auto spec = TurpGameState->CombatPacket.SourceASC->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
	spec.Data->SetSetByCallerMagnitude(GameplayEffectParams.AttributeTag, -UTurpAbilitySystemBlueprintFL::DieRoll(GameplayEffectParams.DieCount, GameplayEffectParams.DieType));
	TurpGameState->CombatPacket.SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, TurpGameState->CombatPacket.TargetASCs[0]);
}
