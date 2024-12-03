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
	PlayerController = Cast<ATurpPlayerController>(
		UGameplayStatics::GetPlayerController(AbilitySystemComponent->GetAvatarActor(), 0));
	PlayerController->AbilityActionTriggered.AddDynamic(this, &UTargetDataUnderMouse::InputCallBack);
}

void UTargetDataUnderMouse::InputCallBack()
{
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	auto ASC = Cast<UAbilitySystemComponent>(
		HitResult.GetActor()->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	
	MouseTargetData.Broadcast(FTurpAbilityTargetData{ASC, HitResult.Location});
	EndTask();
}

void UTargetDataUnderMouse::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	
	PlayerController->AbilityActionTriggered.RemoveDynamic(this, &UTargetDataUnderMouse::InputCallBack);
}



