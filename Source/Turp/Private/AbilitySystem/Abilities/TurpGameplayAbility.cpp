// Copyright Erza.


#include "AbilitySystem/Abilities/TurpGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/Tasks/TargetDataUnderMouse.h"
#include "Game/TurpGameStateBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

FGameplayTag UTurpGameplayAbility::GetAbilityTag() const
{
	return GameplayAbilityProperties.AbilityTag;
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

void UTurpGameplayAbility::FaceTargetBeforeAttacking(const FVector TargetPoint)
{
	const FVector Target = TurpGameState->CombatPacket.Targets.IsEmpty() ? TargetPoint : FindTargetToFaceTowards();
	Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->Execute_FaceTarget(GetAvatarActorFromActorInfo(), Target);
}

void UTurpGameplayAbility::TraceToFindTargets(const FVector TraceCenter, bool ApplyEffect)
{
	TArray<FHitResult> HitResults;
	if( GameplayAbilityProperties.AoeType == EAoeType::Sphere )
	{
		const float Radius = UTurpAbilitySystemBlueprintFL::FootToCentimeter(GameplayAbilityProperties.AoeRange);
		const auto Sphere = FCollisionShape::MakeSphere(Radius);
		GetWorld()->SweepMultiByChannel(HitResults, TraceCenter, TraceCenter, FQuat::Identity, ECC_Visibility, Sphere);
		UKismetSystemLibrary::DrawDebugSphere(this, TraceCenter, Radius, 12, FLinearColor::Red, 5.f);
	}
	// TODO: Handle Box and Cone Collision Shapes

	for (const auto& HitResult : HitResults)
	{
		if(const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor()))
		{
			UTurpAbilitySystemBlueprintFL::AddTargetASCForCombatPacket(TurpGameState, ASC);
		}
	}
	
	if(ApplyEffect)
	{
		UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToAllTargets(TurpGameState);
	}
}


FVector UTurpGameplayAbility::FindTargetToFaceTowards()
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
