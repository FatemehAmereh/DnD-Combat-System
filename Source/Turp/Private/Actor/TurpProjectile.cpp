// Copyright Erza.


#include "Actor/TurpProjectile.h"

// Sets default values
ATurpProjectile::ATurpProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurpProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurpProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

