// Copyright Erza.


#include "TurpAssetManager.h"
#include "TurpTagsManager.h"

UTurpAssetManager& UTurpAssetManager::Get()
{
	check(GEngine);
	
	UTurpAssetManager* AuraAssetManager = Cast<UTurpAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UTurpAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FTurpTagsManager::InitializeNativeGameplayTags();
}
