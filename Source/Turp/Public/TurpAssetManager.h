// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TurpAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TURP_API UTurpAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UTurpAssetManager& Get();
	
protected:
	virtual void StartInitialLoading() override;
};
