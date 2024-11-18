// Copyright Erza.


#include "Actor/ProjectileTargetActor.h"

#include "Actor/TurpProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileTargetActor::AProjectileTargetActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
