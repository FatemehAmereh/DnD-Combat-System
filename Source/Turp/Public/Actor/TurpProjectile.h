// Copyright Erza.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TurpGameplayAbility.h"
#include "GameFramework/Actor.h"
#include "TurpProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TURP_API ATurpProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurpProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(BlueprintReadWrite, Category="Gameplay Effect Settings")
	FGameplayEffectParams GameplayEffectParams;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
