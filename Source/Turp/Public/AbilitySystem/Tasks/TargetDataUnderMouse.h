// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

class ATurpPlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMouseTargetSignature);
/**
 * 
 */
UCLASS()
class TURP_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderMouse* GetTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetSignature MouseTargetData;
	
	virtual void Activate() override;

	UFUNCTION()
	void InputCallBack();

	virtual void OnDestroy(bool bInOwnerFinished) override;

	TObjectPtr<ATurpPlayerController> PlayerController;
};
