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
	UE_LOG(Turp, Log, TEXT("Your log message goes here."));
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

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffect(const ATurpGameStateBase* GameState, const uint8 TargetIndex)
{
	FString DebugMsg = "";
	// Requirement check here.
	const auto& GameplayTags = FTurpTagsManager::Get();
	const FCombatPacket& CP = GameState->CombatPacket;
	const auto& AbilityProperties = CP.AbilityProperties;
	const auto TargetASC = CP.Targets[TargetIndex].ASC;
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	
	// Ability does damage. Do attack roll or saving throw
	if(AbilityProperties.Damage.ModifierTag != FGameplayTag::EmptyTag)
	{
		bool ApplyEffect = true;
		
		// TODO: Check advantage/disadvantage here.
		uint8 DamageRoll = UTurpAbilitySystemBlueprintFL::DieRoll(AbilityProperties.Damage.Dice.Count, AbilityProperties.Damage.Dice.Type);
		if(AbilityProperties.Damage.NeedsSavingThrow)
		{
			uint8 SaveRoll = UTurpAbilitySystemBlueprintFL::DieRoll(1, 20);
			if(AbilityProperties.Damage.SavingThrowTag == GameplayTags.SavingThrow_Strength)
			{
				SaveRoll += TargetAttributeSet->GetStrengthST();
			}
			DebugMsg += FString::Printf(TEXT("SavingThrow: %d > %f\n"), SaveRoll, SourceAttributeSet->GetSpellSaveDC()); 
			if(SaveRoll > SourceAttributeSet->GetSpellSaveDC())
			{
				// Saving throw success.
				if(AbilityProperties.Damage.TakeHalfDamageOnSuccess)
				{
					DamageRoll /= 2.f;
				}
				else
				{
					ApplyEffect = false;
				}
			}
		}
		else
		{
			uint8 AttackRoll = UTurpAbilitySystemBlueprintFL::DieRoll(1, 20);
			AttackRoll += SourceAttributeSet->GetProficiencyBonus() + SourceAttributeSet->GetIntelligenceMod();
			DebugMsg += FString::Printf(TEXT("AttackRoll: %f > %d\n"), TargetAttributeSet->GetArmorClass(), AttackRoll); 
			if(TargetAttributeSet->GetArmorClass() > AttackRoll)
			{
				// Miss!
				ApplyEffect = false;
			}
		}
		
		if(ApplyEffect)
		{
			DebugMsg += FString::Printf(TEXT("Damage: %d\n"), DamageRoll);
			const auto SourceASC = GameState->CombatPacket.SourceASC;
			auto ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddSourceObject(SourceASC);
			auto spec = SourceASC->MakeOutgoingSpec(AbilityProperties.EffectClass, 1, ContextHandle);
			spec.Data->SetSetByCallerMagnitude(AbilityProperties.Damage.ModifierTag, -DamageRoll);
	
			SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, GameState->CombatPacket.Targets[0].ASC);
		}
		GEngine->AddOnScreenDebugMessage(0, 10, FColor::Blue, DebugMsg);
	}
}
