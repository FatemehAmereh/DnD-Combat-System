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
	void SetTargetIndex(const uint8 Index);
	void DisableOverlap();
	void SetTargetASC(UAbilitySystemComponent* ASC);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile Setting")
	float LifeSpan = 200.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	uint8 TargetIndexInCombatPacket = 0;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TObjectPtr<UAbilitySystemComponent> TargetASC;
};
