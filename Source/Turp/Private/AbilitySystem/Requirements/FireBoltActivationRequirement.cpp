// Copyright Erza.


#include "AbilitySystem/Requirements/FireBoltActivationRequirement.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"

bool UFireBoltActivationRequirement::CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect,
                                                                           const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const
{
	// Input ASC is for the target
	// Spec.GetContext().GetInstigatorAbilitySystemComponent()
	const auto AttackerASC = Spec.GetContext().GetInstigatorAbilitySystemComponent();
	const FCombatPacket& CP = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(AttackerASC))->CombatPacket;
	const auto AttackerAS = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const float AbilityAC = UTurpAbilitySystemBlueprintFL::DieRoll(1, 20) + AttackerAS->GetProficiencyBonus() + AttackerAS->GetIntelligenceMod();
	
	const auto EnemyAS = Cast<UTurpAttributeSet>(ASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));

	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Orange, FString::Printf(TEXT("AbilityAC: %f >= EnemyAC: %f"), AbilityAC, EnemyAS->GetArmorClass()));
	return AbilityAC >= EnemyAS->GetArmorClass();
}
