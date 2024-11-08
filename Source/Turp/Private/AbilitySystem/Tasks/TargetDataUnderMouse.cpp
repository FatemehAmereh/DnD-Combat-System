// Copyright Erza.


#include "AbilitySystem/Tasks/TargetDataUnderMouse.h"

#include "EnhancedInputComponent.h"
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

void UTargetDataUnderMouse::InputCallBack(FVector Location)
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Blue, FString("FROM UTargetDataUnderMouse::InputCallBack"));
	MouseTargetData.Broadcast(Location);
	EndTask();
}

void UTargetDataUnderMouse::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	
	PlayerController->AbilityActionTriggered.RemoveDynamic(this, &UTargetDataUnderMouse::InputCallBack);
}



