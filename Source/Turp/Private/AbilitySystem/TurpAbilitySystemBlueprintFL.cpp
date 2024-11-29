// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TurpTagsManager.h"
#include "TurpUtilities.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "AbilitySystem/TurpGameplayEffect.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/TurpPlayerState.h"
#include "UI/HUD/TurpHUD.h"

UOverlayWidgetController* UTurpAbilitySystemBlueprintFL::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if(auto PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(auto HUD = PlayerController->GetHUD<ATurpHUD>())
		{
			auto ASC = PlayerController->GetPlayerState<ATurpPlayerState>()->GetAbilitySystemComponent();
			check(ASC);
			return HUD->GetOverlayWidgetController(ASC);
		}
	}

	return nullptr;
}

void UTurpAbilitySystemBlueprintFL::SetSourceASCForCombatPacket(ATurpGameStateBase* GameState, UAbilitySystemComponent* ASC)
{
	GameState->CombatPacket.SourceASC = ASC;
}

// void UTurpAbilitySystemBlueprintFL::SetEffectPropertiesOfAbilityForCombatPacket(ATurpGameStateBase* GameState,
// 	const FGameplayEffectProperties& EffectProperties)
// {
// 	//GameState->CombatPacket.AbilityProperties.e
// }

void UTurpAbilitySystemBlueprintFL::AddTargetForCombatPacket(ATurpGameStateBase* GameState,
                                                             FTurpAbilityTargetData TargetData)
{
	GameState->CombatPacket.Targets.Add(TargetData);
}

void UTurpAbilitySystemBlueprintFL::AddTargetASCForCombatPacket(ATurpGameStateBase* GameState,
	UAbilitySystemComponent* TargetASC)
{
	FTurpAbilityTargetData TargetData;
	TargetData.ASC = TargetASC;
	TargetData.Location = TargetASC->GetAvatarActor()->GetActorLocation();
	GameState->CombatPacket.Targets.Add(TargetData);
}

void UTurpAbilitySystemBlueprintFL::AddTargetLocationForCombatPacket(ATurpGameStateBase* GameState,
	FVector TargetLocation)
{
	FTurpAbilityTargetData TargetData;
	TargetData.ASC = nullptr;
	TargetData.Location = TargetLocation;
	GameState->CombatPacket.Targets.Add(TargetData);
}

void UTurpAbilitySystemBlueprintFL::SetGameplayAbilityPropertiesForCombatPacket(ATurpGameStateBase* GameState,
                                                                                const FGameplayAbilityProperties& AbilityProperties)
{
	GameState->CombatPacket.AbilityProperties = AbilityProperties;
}

uint8 UTurpAbilitySystemBlueprintFL::RollDie(int Count, int Type)
{
	int DieRollResult = 0;
	for (int i = 0; i < Count; ++i)
	{
		DieRollResult += UKismetMathLibrary::RandomInteger(Type) + 1;
	}
	return DieRollResult;
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToTarget(const ATurpGameStateBase* GameState, const uint8 TargetIndex)
{
	// 1. Apply Effect:
	//		Do the dmg
	//		Apply condition: Add condition tag to stack (Add to ASC containers too?)
	// 2. Add Effect to stack


	// Get relevant variables.
	const FCombatPacket& CP = GameState->CombatPacket;
	const auto& AbilityProperties = CP.AbilityProperties;
	const auto EffectInfo = GameState->GameplayEffectInformation->GetEffectInfoWithTag(AbilityProperties.AbilityTag);
	const auto TargetASC = CP.Targets[TargetIndex].ASC;
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));

	FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";

	// Do Damage.
	if(EffectInfo->Damage.DoesDamage)
	{

		// TODO: Check advantage/disadvantage here.
		const bool SucceededSavingThrow = MakeSavingThrow(EffectInfo->Damage.SavingThrowTag, *SourceAttributeSet, *TargetAttributeSet, DebugMsg);
		const bool IsHit = MakeAttackRoll(*SourceAttributeSet, *TargetAttributeSet, DebugMsg);
		
		// Target should take damage if it:
		// 1. Failed the saving throw
		// 2. Saved the saving throw but still takes half damage.
		// 3. Got hit.
		if(IsHit || !SucceededSavingThrow || (SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess))
		{
			int8 DamageRoll = RollDie(EffectInfo->Damage.Dice.Count, EffectInfo->Damage.Dice.Type);
			if(SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess)
			{
				DamageRoll *= 0.5f;
			}
			DebugMsg += FString::Printf(TEXT("Damage (%dd%d): %d\n"), EffectInfo->Damage.Dice.Count,EffectInfo->Damage.Dice.Type, DamageRoll);
			const auto SourceASC = GameState->CombatPacket.SourceASC;
			auto ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddSourceObject(SourceASC);
			const auto spec = SourceASC->MakeOutgoingSpec(GameState->DefaultDamageGameplayEffect, 1, ContextHandle);
			spec.Data->SetSetByCallerMagnitude(FTurpTagsManager::Get().DamageModifier, -DamageRoll);
			
			// How to grant tags
			//spec.Data->DynamicGrantedTags.AddTag(FTurpTagsManager::Get().SavingThrow_Charisma);
			
			SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, TargetASC);
		}
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}

	// Apply condition
	if(!EffectInfo->Condition.TagsToGrant.IsEmpty())
	{
		// Requires saving throw.
		if(EffectInfo->Condition.SavingThrowTag != FGameplayTag::EmptyTag)
		{
		
		}
	}
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToAllTargets(const ATurpGameStateBase* GameState)
{
	for (int i = 0; i < GameState->CombatPacket.Targets.Num(); ++i)
	{
		ApplyGameplayEffectToTarget(GameState, i);
	}
}

bool UTurpAbilitySystemBlueprintFL::MakeSavingThrow(const FGameplayTag& SavingThrowTag,
	const UTurpAttributeSet& SourceAS, const UTurpAttributeSet& TargetAS, FString& DebugMsg)
{
	if(SavingThrowTag == FGameplayTag::EmptyTag)
	{
		return false;
	}
	
	bool IsSuccess = false;
	const uint8 DiceRoll = RollDie(1, 20);
	const uint8 SavingThrowModifier = static_cast<uint8>(GetSavingThrowModifier(TargetAS, SavingThrowTag));
	const uint8 SaveRoll = DiceRoll + SavingThrowModifier;
			
	if(SaveRoll > SourceAS.GetSpellSaveDC())
	{
		// Saving throw success.
		DebugMsg += TEXT("SavingThrow succeded! ");
		IsSuccess = true;
	}
	else
	{
		DebugMsg += TEXT("SavingThrow Failed! ");
	}
	DebugMsg += FString::Printf(TEXT("SpellSaveDC:%d, SaveRoll:%d= %d(1d20) + %d(STMod)\n"), StaticCast<int>(SourceAS.GetSpellSaveDC()), SaveRoll, DiceRoll, SavingThrowModifier);
	return IsSuccess;
}

float UTurpAbilitySystemBlueprintFL::GetSavingThrowModifier(const UTurpAttributeSet& AttributeSet,
                                                            const FGameplayTag SavingThrowTag)
{
	const auto& GameplayTags = FTurpTagsManager::Get();
	if(SavingThrowTag == GameplayTags.SavingThrow_Strength)
	{
		return AttributeSet.GetStrengthST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Dexterity)
	{
		return AttributeSet.GetDexterityST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Constitution)
	{
		return AttributeSet.GetConstitutionST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Intelligence)
	{
		return AttributeSet.GetIntelligenceST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Wisdom)
	{
		return AttributeSet.GetWisdomST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Charisma)
	{
		return AttributeSet.GetCharismaST();
	}

	UE_LOG(Turp, Error, TEXT("SavingThrow tag of this ability is invalid! Can't retrieve saving throw mod from AS."))
	return 0.f;
}

bool UTurpAbilitySystemBlueprintFL::MakeAttackRoll(const UTurpAttributeSet& SourceAS, const UTurpAttributeSet& TargetAS,
	FString& DebugMsg)
{
	bool IsHit = false;
	const uint8 DiceRoll = RollDie(1, 20);
	const uint8 BonusMods = static_cast<uint8>(SourceAS.GetProficiencyBonus() + SourceAS.GetIntelligenceMod());
	const uint8 AttackRoll = DiceRoll + BonusMods;
	const uint8 AC = static_cast<uint8>(TargetAS.GetArmorClass() + TargetAS.GetDexterityMod());
			
	if(AC > AttackRoll)
	{
		// Miss!
		DebugMsg += TEXT("Attack Miss! ");
	}
	else
	{
		// Hit!
		DebugMsg += TEXT("Attack Hit! ");
		IsHit = true;
	}
	DebugMsg += FString::Printf(TEXT("AC:%d, AttackRoll:%d= %d(1d20) + %d(BonusMods)\n"), AC, AttackRoll, DiceRoll, BonusMods);
	return IsHit;
}