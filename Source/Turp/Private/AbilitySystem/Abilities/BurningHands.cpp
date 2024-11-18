// Copyright Erza.


#include "AbilitySystem/Abilities/BurningHands.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "Kismet/KismetSystemLibrary.h"

void UBurningHands::ConeTrace(FVector MouseHitLocation)
{
	float SpellRangeInMeters = GameplayAbilityProperties.Range / 3.281f * 100.f;
	
	// Create a box trace.
	FVector HitDirection = MouseHitLocation - GetAvatarActorFromActorInfo()->GetActorLocation();
	HitDirection.Normalize();
	FVector BoxCenter = GetAvatarActorFromActorInfo()->GetActorLocation() + HitDirection * FVector(SpellRangeInMeters);
	auto Box = FCollisionShape::MakeBox(FVector(SpellRangeInMeters));
	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	// UKismetSystemLibrary::BoxTraceMulti(GetAvatarActorFromActorInfo(), BoxCenter,
	// 	BoxCenter, FVector(SpellRangeInMeters,SpellRangeInMeters, 0), FRotator(0,0,0),
	// 	ECC_Visibility,false, ActorsToIgnore, EDrawDebugTrace::Type::Persistent,
	// 	HitResults, true);

	GetWorld()->SweepMultiByChannel(HitResults, BoxCenter, BoxCenter, FQuat::Identity, ECC_Visibility, Box);
	
	for (auto HitResult : HitResults)
	{
		auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if(ASC)
		{
			FTurpAbilityTargetData Target;
			Target.ASC = ASC;
			UTurpAbilitySystemBlueprintFL::AddTargetForCombatPacket(TurpGameState, Target);
		}
	}
	auto c = TurpGameState->CombatPacket;
	
}
