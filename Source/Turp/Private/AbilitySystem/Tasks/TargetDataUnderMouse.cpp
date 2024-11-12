// Copyright Erza.


#include "AbilitySystem/Tasks/TargetDataUnderMouse.h"

#include "EnhancedInputComponent.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TurpPlayerController.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::GetTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
}

void UTargetDataUnderMouse::Activate()
{
	PlayerController = Cast<ATurpPlayerController>(Ability->GetActorInfo().PlayerController);
	PlayerController->AbilityActionTriggered.AddDynamic(this, &UTargetDataUnderMouse::InputCallBack);
}

void UTargetDataUnderMouse::InputCallBack()
{
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	auto ASC = Cast<UTurpAbilitySystemComponent>(HitResult.GetActor()->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	auto GameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_TargetASC(GameState, ASC);
	UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_TargetLocation(GameState, HitResult.Location);
	
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, 	HitResult.GetActor()->GetName());
	
	MouseTargetData.Broadcast();
	EndTask();
}

void UTargetDataUnderMouse::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	
	PlayerController->AbilityActionTriggered.RemoveDynamic(this, &UTargetDataUnderMouse::InputCallBack);
}



