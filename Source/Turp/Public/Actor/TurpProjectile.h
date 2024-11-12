// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurpProjectile.generated.h"

UCLASS()
class TURP_API ATurpProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurpProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
