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
	// Requirement check here.
	const auto& GameplayTags = FTurpTagsManager::Get();
	const FCombatPacket& CP = GameState->CombatPacket;
	const auto& AbilityProperties = CP.AbilityProperties;
	const auto TargetASC = CP.Targets[TargetIndex].ASC;
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	FString DebugMsg = "";
	
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
			if(AbilityProperties.Damage.SavingThrowTag == GameplayTags.SavingThrow_Dexterity)
			{
				SaveRoll += TargetAttributeSet->GetDexterityST();
			}

			if(SaveRoll > SourceAttributeSet->GetSpellSaveDC())
			{
				// Saving throw success.
				DebugMsg += TEXT("SavingThrow succeded! ");
				if(AbilityProperties.Damage.TakeHalfDamageOnSuccess)
				{
					DamageRoll /= 2.f;
				}
				else
				{
					ApplyEffect = false;
				}
			}
			else
			{
				DebugMsg += TEXT("SavingThrow Failed! ");
			}
			DebugMsg += FString::Printf(TEXT("SpellSaveDC:%d, SaveRoll:%d "), StaticCast<int>(SourceAttributeSet->GetSpellSaveDC()), SaveRoll);
		}
		else
		{
			uint8 AttackRoll = UTurpAbilitySystemBlueprintFL::DieRoll(1, 20);
			AttackRoll += SourceAttributeSet->GetProficiencyBonus() + SourceAttributeSet->GetIntelligenceMod();

			if(TargetAttributeSet->GetArmorClass() > AttackRoll)
			{
				// Miss!
				DebugMsg += TEXT("Attack Miss! ");
				ApplyEffect = false;
			}
			else
			{
				DebugMsg += TEXT("Attack Hit! ");
			}
			DebugMsg += FString::Printf(TEXT("AC:%d, AttackRoll:%d "), StaticCast<int>(TargetAttributeSet->GetArmorClass()), AttackRoll);
		}
		
		if(ApplyEffect)
		{
			DebugMsg += FString::Printf(TEXT("Damage (%dd%d): %d\n"), AbilityProperties.Damage.Dice.Count, AbilityProperties.Damage.Dice.Type, DamageRoll);
			const auto SourceASC = GameState->CombatPacket.SourceASC;
			auto ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddSourceObject(SourceASC);
			auto spec = SourceASC->MakeOutgoingSpec(AbilityProperties.EffectClass, 1, ContextHandle);
			spec.Data->SetSetByCallerMagnitude(AbilityProperties.Damage.ModifierTag, -DamageRoll);
	
			SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, GameState->CombatPacket.Targets[0].ASC);
		}
		GEngine->AddOnScreenDebugMessage(0, 10, FColor::Blue, DebugMsg);
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToAllTargets(const ATurpGameStateBase* GameState)
{
	for (int i = 0; i < GameState->CombatPacket.Targets.Num(); ++i)
	{
		ApplyGameplayEffectToTarget(GameState, i);
	}
}	
