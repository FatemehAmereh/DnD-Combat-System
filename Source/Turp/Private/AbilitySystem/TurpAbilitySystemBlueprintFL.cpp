// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TurpTagsManager.h"
#include "TurpUtilities.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "AbilitySystem/Requirements/FireBoltActivationRequirement.h"
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

uint8 UTurpAbilitySystemBlueprintFL::DieRoll(int Count, int Type)
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
	const FCombatPacket& CP = GameState->CombatPacket;
	const auto& AbilityProperties = CP.AbilityProperties;
	const auto TargetASC = CP.Targets[TargetIndex].ASC;
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";
	
	// Ability does damage. Do attack roll or saving throw
	if(AbilityProperties.Damage.ModifierTag != FGameplayTag::EmptyTag)
	{
		bool ShouldApplyEffect = true;
		
		// TODO: Check advantage/disadvantage here.
		uint8 DamageRoll = DieRoll(AbilityProperties.Damage.Dice.Count, AbilityProperties.Damage.Dice.Type);
		if(AbilityProperties.Damage.NeedsSavingThrow)
		{
			const uint8 DiceRoll = DieRoll(1, 20);
			const uint8 SavingThrowModifier = static_cast<uint8>(GetSavingThrowModifier(TargetAttributeSet, AbilityProperties.Damage.SavingThrowTag));
			const uint8 SaveRoll = DiceRoll + SavingThrowModifier;
			
			if(SaveRoll > SourceAttributeSet->GetSpellSaveDC())
			{
				// Saving throw success.
				DebugMsg += TEXT("SavingThrow succeded! ");
				if(AbilityProperties.Damage.TakeHalfDamageOnSuccess)
				{
					DamageRoll *= 0.5f;
				}
				else
				{
					ShouldApplyEffect = false;
				}
			}
			else
			{
				DebugMsg += TEXT("SavingThrow Failed! ");
			}
			DebugMsg += FString::Printf(TEXT("SpellSaveDC:%d, SaveRoll:%d= %d(1d20) + %d(STMod)\n"), StaticCast<int>(SourceAttributeSet->GetSpellSaveDC()), SaveRoll, DiceRoll, SavingThrowModifier);
		}
		else
		{
			const uint8 DiceRoll = DieRoll(1, 20);
			const uint8 BonusMods = static_cast<uint8>(SourceAttributeSet->GetProficiencyBonus() + SourceAttributeSet->GetIntelligenceMod());
			const uint8 AttackRoll = DiceRoll + BonusMods;

			if(TargetAttributeSet->GetArmorClass() > AttackRoll)
			{
				// Miss!
				DebugMsg += TEXT("Attack Miss! ");
				ShouldApplyEffect = false;
			}
			else
			{
				// Hit!
				DebugMsg += TEXT("Attack Hit! ");
			}
			DebugMsg += FString::Printf(TEXT("AC:%d, AttackRoll:%d= %d(1d20) + %d(BonusMods)\n"), StaticCast<int>(TargetAttributeSet->GetArmorClass()), AttackRoll, DiceRoll, BonusMods);
		}

		// Attack hit or saving throw fail but takes half damage.
		if(ShouldApplyEffect)
		{
			DebugMsg += FString::Printf(TEXT("Damage (%dd%d): %d\n"), AbilityProperties.Damage.Dice.Count, AbilityProperties.Damage.Dice.Type, DamageRoll);
			const auto SourceASC = GameState->CombatPacket.SourceASC;
			auto ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddSourceObject(SourceASC);
			const auto spec = SourceASC->MakeOutgoingSpec(AbilityProperties.EffectClass, 1, ContextHandle);
			spec.Data->SetSetByCallerMagnitude(AbilityProperties.Damage.ModifierTag, -DamageRoll);
	
			SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, TargetASC);
		}
		
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}
	
	// TODO: Check applying condition.
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToAllTargets(const ATurpGameStateBase* GameState)
{
	for (int i = 0; i < GameState->CombatPacket.Targets.Num(); ++i)
	{
		ApplyGameplayEffectToTarget(GameState, i);
	}
}

float UTurpAbilitySystemBlueprintFL::GetSavingThrowModifier(const UTurpAttributeSet* AttributeSet,
	const FGameplayTag SavingThrowTag)
{
	const auto& GameplayTags = FTurpTagsManager::Get();
	if(SavingThrowTag == GameplayTags.SavingThrow_Strength)
	{
		return AttributeSet->GetStrengthST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Dexterity)
	{
		return AttributeSet->GetDexterityST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Constitution)
	{
		return AttributeSet->GetConstitutionST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Intelligence)
	{
		return AttributeSet->GetIntelligenceST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Wisdom)
	{
		return AttributeSet->GetWisdomST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Charisma)
	{
		return AttributeSet->GetCharismaST();
	}

	UE_LOG(Turp, Error, TEXT("SavingThrow tag of this ability is invalid! Can't retrieve saving throw mod from AS."))
	return 0.f;
}	
