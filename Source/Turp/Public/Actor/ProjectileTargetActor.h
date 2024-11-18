// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileTargetActor.generated.h"

class USphereComponent;

UCLASS()
class TURP_API AProjectileTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileTargetActor();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;
};
