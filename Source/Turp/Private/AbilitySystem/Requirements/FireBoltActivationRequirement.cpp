// Copyright Erza.


#include "AbilitySystem/Requirements/FireBoltActivationRequirement.h"

#include "TurpTagsManager.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"

bool UFireBoltActivationRequirement::CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect,
                                                                           const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const
{
	// Input ASC is for the target.
	// const auto& GameplayTags = FTurpTagsManager::Get();
	// const FCombatPacket& CP = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(ASC))->CombatPacket;
	// const auto& AbilityProperties = CP.AbilityProperties;
	// const auto TargetAttributeSet = Cast<UTurpAttributeSet>(ASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	// const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	//
	// // Ability does damage.
	// if(AbilityProperties.Damage.ModifierTag != FGameplayTag::EmptyTag)
	// {
	// 	// TODO: Check advantage/disadvantage here.
	// 	bool TargetSaved = false;
	// 	if(AbilityProperties.Damage.NeedsSavingThrow)
	// 	{
	// 		uint8 SaveRoll = UTurpAbilitySystemBlueprintFL::DieRoll(1, 20);
	// 		if(AbilityProperties.Damage.SavingThrowTag == GameplayTags.SavingThrow_Strength)
	// 		{
	// 			SaveRoll += TargetAttributeSet->GetStrengthST();
	// 		}
	// 		
	// 		if(SaveRoll > SourceAttributeSet->GetSpellSaveDC())
	// 		{
	// 			TargetSaved = true;
	// 		}
	// 	}

		// // Roll Damage
		// if(!TargetSaved || (TargetSaved && AbilityProperties.Damage.TakeHalfDamageOnSave))
		// {
		// 	uint8 DamageRoll = UTurpAbilitySystemBlueprintFL::DieRoll(AbilityProperties.Damage.Dice.Count, AbilityProperties.Damage.Dice.Type);
		// 	if(TargetSaved && AbilityProperties.Damage.TakeHalfDamageOnSave)
		// 	{
		// 		DamageRoll /= 2.f;
		// 	}
		// }
	//}
	return true;
}
