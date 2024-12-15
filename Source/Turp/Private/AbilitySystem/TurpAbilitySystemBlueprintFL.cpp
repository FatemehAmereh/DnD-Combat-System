// Copyright Erza.


#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TurpTagsManager.h"
#include "TurpUtilities.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "AbilitySystem/TurpAttributeSet.h"
#include "Character/TurpCharacterBase.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"

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

int UTurpAbilitySystemBlueprintFL::RollDie(const int Count, const int Type)
{
	// Constant value. Used for adding a modifier to rolls.
	if(Count == 0)
	{
		return Type;
	}
	
	int DieRollResult = 0;
	for (int i = 0; i < FMath::Abs(Count); ++i)
	{
		DieRollResult += UKismetMathLibrary::RandomInteger(Type) + 1;
	}
	return Count >= 0 ? DieRollResult : -DieRollResult;
}

int UTurpAbilitySystemBlueprintFL::RollDie(const FDice Dice)
{
	return RollDie(Dice.Count, Dice.Type);
}

void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToTarget(const ATurpGameStateBase& GameState, const uint8 TargetIndex)
{
	// 1. Apply Effect:
	//		Do the dmg
	//		Apply condition: Add condition tag to stack (Add to ASC containers too?)
	// 2. Add Effect to stack
	
	// Get relevant variables.
	const FCombatPacket& CP = GameState.CombatPacket;
	const auto& AbilityProperties = CP.AbilityProperties;
	const auto EffectInfo = GameState.GameplayEffectInformation->GetEffectInfoWithTag(AbilityProperties.AbilityTag);
	const auto TargetASC = Cast<UTurpAbilitySystemComponent>(CP.Targets[TargetIndex].ASC);
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	const auto SourceAttributeSet = Cast<UTurpAttributeSet>(CP.SourceASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));

	uint8 DamageSaveDC = 0;
	// Do Damage.
	if(EffectInfo->Damage.DoesDamage)
	{
		FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";
		
		bool SucceededSavingThrow = false;
		const bool NeedsSavingThrow = EffectInfo->Damage.SavingThrowTag == FGameplayTag::EmptyTag ? false : true;
		bool IsHit = false;
		if(NeedsSavingThrow)
		{
			const auto SavingThrowResult = MakeSavingThrow(EffectInfo->Damage.SavingThrowTag, GameState, TargetASC,
			SourceAttributeSet, 0, TargetAttributeSet, DebugMsg);
			SucceededSavingThrow = SavingThrowResult.Key;
			DamageSaveDC = SavingThrowResult.Value;
		}
		else
		{
			const auto SourceASC = Cast<UTurpAbilitySystemComponent>(GameState.CombatPacket.SourceASC);
			IsHit = MakeAttackRoll(GameState, *SourceASC, *TargetASC, *SourceAttributeSet,
				*TargetAttributeSet, DebugMsg);	
		}
		
		
		// Target should take damage if it:
		// 1. Needed to do a saving throw and either
		//		Failed the saving throw or
		//		Saved the saving throw but still takes half damage
		// 2. Needed attack roll and got hit
		// 3. Automatically hit
		const bool TakeDamageBasedOnSavingThrow = NeedsSavingThrow && (!SucceededSavingThrow || (SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess));
		if(IsHit || TakeDamageBasedOnSavingThrow)
		{
			int8 DamageRoll = RollDie(EffectInfo->Damage.Dice.Count, EffectInfo->Damage.Dice.Type);
			if(SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess)
			{
				DamageRoll *= 0.5f;
			}
			DebugMsg += FString::Printf(TEXT("Damage (%dd%d): %d\n"), EffectInfo->Damage.Dice.Count,EffectInfo->Damage.Dice.Type, DamageRoll);
			const auto SourceASC = GameState.CombatPacket.SourceASC;
			auto ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddSourceObject(SourceASC);
			const auto spec = SourceASC->MakeOutgoingSpec(GameState.DefaultDamageGameplayEffect, 1, ContextHandle);
			spec.Data->SetSetByCallerMagnitude(FTurpTagsManager::Get().DamageModifier, -DamageRoll);
			
			SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, TargetASC);
		}
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}
	
	bool ConditionApplied = false;
	uint8 ConditionSpellSaveDC = 0;
	// Apply condition.
	if(!EffectInfo->Condition.TagsToGrant.IsEmpty())
	{
		FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";
		
		bool ApplyCondition = false;
		if(EffectInfo->Condition.SavingThrowTag == FGameplayTag::EmptyTag)
		{
			// Automatically apply the condition.
			ApplyCondition = true;
		}
		else
		{
			// [IsSuccess, SaveDC]
			const auto SavingThrowResult = MakeSavingThrow(EffectInfo->Condition.SavingThrowTag,
				GameState, TargetASC, SourceAttributeSet, 0, TargetAttributeSet, DebugMsg);
			ApplyCondition = !SavingThrowResult.Key;
			ConditionSpellSaveDC = SavingThrowResult.Value;
		}
		
		if(ApplyCondition)
		{
			for (const auto& ConditionTag : EffectInfo->Condition.TagsToGrant)
			{
				TargetASC->AddCondition(ConditionTag);
			}
			ConditionApplied = true;
		}
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}
	
	// Add Effect to active Effect stack on Target if it has duration.
	if(EffectInfo->Duration != 0)
	{
		TargetASC->AddEffect(AbilityProperties.AbilityTag, EffectInfo->Duration, EffectInfo->CanStack, DamageSaveDC, ConditionApplied, ConditionSpellSaveDC);
	}
}

void UTurpAbilitySystemBlueprintFL::ReapplyActiveGameplayEffect(const ATurpGameStateBase& GameState, const FGameplayTag& EffectTag, const FEffectStackElement& EffectStackElement,
	UTurpAbilitySystemComponent* TargetASC)
{
	const auto EffectInfo = GameState.GameplayEffectInformation->GetEffectInfoWithTag(EffectTag);
	const auto TargetAttributeSet = Cast<UTurpAttributeSet>(TargetASC->GetAttributeSet(UTurpAttributeSet::StaticClass()));
	
	if(EffectInfo->Damage.DoesDamage && EffectInfo->Damage.ApplyDamageEveryTurn)
	{
		// Reapply Damage
		FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";
		
		bool SucceededSavingThrow = false;
		const bool NeedsSavingThrow = EffectInfo->Damage.SavingThrowTag == FGameplayTag::EmptyTag ? false : true;
		bool IsHit = false;
		if(NeedsSavingThrow)
		{
			const auto SavingThrowResult = MakeSavingThrow(EffectInfo->Damage.SavingThrowTag, GameState, TargetASC,
			nullptr, EffectStackElement.DamageSaveDC, TargetAttributeSet, DebugMsg);
			SucceededSavingThrow = SavingThrowResult.Key;
		}

		if(NeedsSavingThrow && (!SucceededSavingThrow || (SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess)))
		{
			const bool TakeDamageBasedOnSavingThrow = NeedsSavingThrow && (!SucceededSavingThrow || (SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess));
			if(IsHit || TakeDamageBasedOnSavingThrow)
			{
				int8 DamageRoll = RollDie(EffectInfo->Damage.Dice.Count, EffectInfo->Damage.Dice.Type);
				if(SucceededSavingThrow && EffectInfo->Damage.TakeHalfDamageOnSuccess)
				{
					DamageRoll *= 0.5f;
				}
				DebugMsg += FString::Printf(TEXT("Damage (%dd%d): %d\n"), EffectInfo->Damage.Dice.Count,EffectInfo->Damage.Dice.Type, DamageRoll);
				const auto SourceASC = GameState.CombatPacket.SourceASC;
				auto ContextHandle = SourceASC->MakeEffectContext();
				ContextHandle.AddSourceObject(SourceASC);
				const auto spec = SourceASC->MakeOutgoingSpec(GameState.DefaultDamageGameplayEffect, 1, ContextHandle);
				spec.Data->SetSetByCallerMagnitude(FTurpTagsManager::Get().DamageModifier, -DamageRoll);
			
				SourceASC->ApplyGameplayEffectSpecToTarget(*spec.Data, TargetASC);
			}
		}
		UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
	}

	if(!EffectInfo->Condition.TagsToGrant.IsEmpty())
	{
		if(EffectInfo->Condition.SavingThrowTag != FGameplayTag::EmptyTag)
		{
			FString DebugMsg = TargetASC->GetAvatarActor()->GetName() + ":\n";
			
			// Check if the granted Effect should be removed.
			const auto SavingThrowResult = MakeSavingThrow(EffectInfo->Condition.SavingThrowTag, GameState, TargetASC, nullptr, EffectStackElement.ConditionSpellSaveDC, TargetAttributeSet, DebugMsg);
			const bool SucceededSavingThrow = SavingThrowResult.Key;
			if(SucceededSavingThrow)
			{
				// Remove Effect.
				TargetASC->RemoveEffect(EffectTag, 1);
			}
			UE_LOG(Turp, Log, TEXT("%s"), *DebugMsg);
		}
	}
}


void UTurpAbilitySystemBlueprintFL::ApplyGameplayEffectToAllTargets(const ATurpGameStateBase* GameState)
{
	for (int i = 0; i < GameState->CombatPacket.Targets.Num(); ++i)
	{
		ApplyGameplayEffectToTarget(*GameState, i);
	}
}

TTuple<bool, uint8> UTurpAbilitySystemBlueprintFL::MakeSavingThrow(const FGameplayTag& SavingThrowTag, const ATurpGameStateBase& GameState,
	const UTurpAbilitySystemComponent* TargetASC, const UTurpAttributeSet* SourceAS, const uint8 PreRecordedSaveDC, const UTurpAttributeSet* TargetAS,
	FString& DebugMsg)
{
	if(SavingThrowTag == FGameplayTag::EmptyTag)
	{
		// No need for saving throw. This Effect doesn't require one.
		return {false, 0};
	}
	
	bool IsSuccess = false;
	FString RollDebugMsg = "";	
	const auto ActionCheck = MakeActionCheck(GetActionEnumForTag(SavingThrowTag), *TargetASC, GameState, RollDebugMsg);
	if(!ActionCheck.Key)
	{
		// Saving throw Fail.
		DebugMsg += TEXT("SavingThrow Failed! ");
		DebugMsg += RollDebugMsg;
		DebugMsg += "\n";
		return {false, 0};
	}
	else
	{
		const uint8 DiceRoll = ActionCheck.Value;
        const uint8 SavingThrowModifier = static_cast<uint8>(GetSavingThrowModifier(*TargetAS, SavingThrowTag, RollDebugMsg));
        const uint8 SaveRoll = DiceRoll + SavingThrowModifier;
    
        const uint8 SaveDC = SourceAS ? SourceAS->GetSpellSaveDC() : PreRecordedSaveDC;
        if(SaveRoll >= SaveDC)
        {
        	// Saving throw success.
        	DebugMsg += TEXT("SavingThrow succeded! ");
        	IsSuccess = true;
        }
        else
        {
        	// Saving throw Fail.
        	DebugMsg += TEXT("SavingThrow Failed! ");
        }
        DebugMsg += FString::Printf(TEXT("SpellSaveDC:%d, SaveRoll:%d = "),
        	StaticCast<int>(SaveDC), SaveRoll);
		DebugMsg += RollDebugMsg;
		return {IsSuccess, SaveDC};
	}
}

bool UTurpAbilitySystemBlueprintFL::MakeAttackRoll(const ATurpGameStateBase& GameState, const UTurpAbilitySystemComponent& SourceASC,
	const UTurpAbilitySystemComponent& TargetASC, const UTurpAttributeSet& SourceAS, const UTurpAttributeSet& TargetAS, FString& DebugMsg)
{
	bool IsHit = false;

	FString RollDebugMsg = "";
	const auto ActionCheck= MakeActionCheck(EActionEnum::AtkRoll, SourceASC, GameState, RollDebugMsg);
	if(!ActionCheck.Key)
	{
		// Attack Miss!
		DebugMsg += TEXT("Attack Miss! AttackRoll: ");
		DebugMsg += RollDebugMsg;
	}
	else
	{
		uint8 DiceRoll = ActionCheck.Value;
		const float ClassSpecificAttackMod = Cast<ATurpCharacterBase>(SourceASC.GetAvatarActor())->GetClassSpecificAttackRollModifier(RollDebugMsg);
		const float ProficiencyBonus = static_cast<uint8>(SourceAS.GetProficiencyBonus());
		RollDebugMsg += FString::Printf(TEXT(" + %d(ProficiencyBonus) "), static_cast<uint8>(ProficiencyBonus));
		const uint8 BonusMods = static_cast<uint8>(SourceAS.GetProficiencyBonus() + ClassSpecificAttackMod);
		const uint8 AttackRoll = DiceRoll + BonusMods;
		const uint8 AC = static_cast<uint8>(TargetAS.GetArmorClass() + TargetAS.GetDexterityMod());
			
		if(AttackRoll >= AC)
		{
			// Attack Hit!
			DebugMsg += TEXT("Attack Hit! ");
			IsHit = true;
		}
		else
		{
			// Attack Miss!
			DebugMsg += TEXT("Attack Miss! ");
		}
		DebugMsg += FString::Printf(TEXT("AC:%d, AttackRoll:%d = "), AC, AttackRoll);
		DebugMsg += RollDebugMsg;
	}
	DebugMsg += "\n";
	return IsHit;
}

TTuple<bool, uint8> UTurpAbilitySystemBlueprintFL::MakeActionCheck(const EActionEnum Action, const UTurpAbilitySystemComponent& ASC,
	const ATurpGameStateBase& GameState, FString& DebugMsg)
{
	// TODO: add debugging information about what condition gave what status.
	
	const auto ConditionStack = ASC.GetConditionStackForAction(Action);
	if(!ConditionStack)
	{
		UE_LOG(Turp, Log, TEXT("%s"), *FString("[TurpAbilitySystemBlueprintFL] Action Enum Doesn't exist on Condition Stack!"));
		return {false, 0};;
	}
	
	if(!ConditionStack->ActionStatusMap.Find(EStatusEnum::AutoSave)->IsEmpty())
	{
		// Auto Save.
		DebugMsg += FString::Printf(TEXT("100(%hs) "), "AutoSave");
		return {true, 100};
	}
	
	if(!ConditionStack->ActionStatusMap.Find(EStatusEnum::AutoFail)->IsEmpty())
	{
		// Auto Fail.
		DebugMsg += FString::Printf(TEXT("0(%hs) "), "AutoFail");
		return {false, 0};
	}

	int RollResult = 0;
	int AdvantageCount = 0;
	int DisadvantageCount = 0;
	{
		const auto TagContainer = ConditionStack->ActionStatusMap.Find(EStatusEnum::Advantage);
		AdvantageCount = TagContainer->Num();
	}
	{
		const auto TagContainer = ConditionStack->ActionStatusMap.Find(EStatusEnum::Disadvantage);
		DisadvantageCount = TagContainer->Num();
	}
	
	if(AdvantageCount > DisadvantageCount)
	{
		RollResult = FMath::Max(RollDie(1, 20), RollDie(1, 20));
		DebugMsg += FString::Printf(TEXT("%d(1d20 %hs) "), RollResult, "Advantage");
	}
	if(AdvantageCount < DisadvantageCount)
	{
		RollResult = FMath::Min(RollDie(1, 20), RollDie(1, 20));
		DebugMsg += FString::Printf(TEXT("%d(1d20 %hs) "), RollResult, "Disadvantage");
	}
	else
	{
		RollResult = RollDie(1, 20);
		DebugMsg += FString::Printf(TEXT("%d(1d20) "), RollResult);
	}

	int Modifier = 0;
	const auto& ConditionTagContainer = *ConditionStack->ActionStatusMap.Find(EStatusEnum::Modifier);
	for (const auto& ConditionTag : ConditionTagContainer)
	{
		const auto ActionStatus = GameState.GameplayConditionInformation->GetActionStatus(ConditionTag, Action);
		if(ActionStatus->StatusEnum == EStatusEnum::Modifier)
		{
			auto Mod = RollDie(ActionStatus->ModifierDice);
			DebugMsg += FString::Printf(TEXT("+ %d(%s) "), Mod, *ConditionTag.GetTagName().ToString());
			Modifier += Mod;
		}
	}

	return {true, RollResult + Modifier};
}

EActionEnum UTurpAbilitySystemBlueprintFL::GetActionEnumForTag(const FGameplayTag& SavingThrowTag)
{
	const auto& GameplayTags = FTurpTagsManager::Get();
	if(SavingThrowTag == GameplayTags.SavingThrow_Strength)
	{
		return EActionEnum::StrST;
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Dexterity)
	{
		return EActionEnum::DexST;
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Constitution)
	{
		return EActionEnum::ConST;
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Intelligence)
	{
		return EActionEnum::IntST;
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Wisdom)
	{
		return EActionEnum::WisST;
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Charisma)
	{
		return EActionEnum::ChaST;
	}

	UE_LOG(Turp, Error, TEXT("SavingThrow tag of this ability is invalid! Can't retrieve saving throw mod from AS."))
	return EActionEnum::ConST;
}

float UTurpAbilitySystemBlueprintFL::GetSavingThrowModifier(const UTurpAttributeSet& AttributeSet,
                                                            const FGameplayTag& SavingThrowTag, FString& DebugMsg)
{
	const auto& GameplayTags = FTurpTagsManager::Get();
	if(SavingThrowTag == GameplayTags.SavingThrow_Strength)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(StrengthSavingThrow) "),
			StaticCast<int>(AttributeSet.GetStrengthST()));
		return AttributeSet.GetStrengthST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Dexterity)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(DexteritySavingThrow) "),
			StaticCast<int>(AttributeSet.GetDexterityST()));
		return AttributeSet.GetDexterityST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Constitution)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(ConstitutionSavingThrow) "),
			StaticCast<int>(AttributeSet.GetConstitutionST()));
		return AttributeSet.GetConstitutionST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Intelligence)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(IntelligenceSavingThrow) "),
			StaticCast<int>(AttributeSet.GetIntelligenceST()));
		return AttributeSet.GetIntelligenceST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Wisdom)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(WisdomSavingThrow) "),
			StaticCast<int>(AttributeSet.GetWisdomST()));
		return AttributeSet.GetWisdomST();
	}
	else if(SavingThrowTag == GameplayTags.SavingThrow_Charisma)
	{
		DebugMsg += FString::Printf(TEXT(" + %d(CharismaSavingThrow) "),
			StaticCast<int>(AttributeSet.GetCharismaST()));
		return AttributeSet.GetCharismaST();
	}

	UE_LOG(Turp, Error, TEXT("SavingThrow tag of this ability is invalid! Can't retrieve saving throw mod from AS."))
	return 0.f;
}
