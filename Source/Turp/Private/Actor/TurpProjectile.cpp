// Copyright Erza.


#include "Actor/TurpProjectile.h"

#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATurpProjectile::ATurpProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
    ProjectileMovement->InitialSpeed = 550.f;
    ProjectileMovement->MaxSpeed = 550.f;
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ATurpProjectile::SetGameplayEffectParams(const FGameplayEffectParams& EffectParams)
{
	GameplayEffectParams = EffectParams;
}

void ATurpProjectile::DisableOverlap()
{
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ATurpProjectile::SetTargetASC(UAbilitySystemComponent* ASC)
{
	TargetASC = ASC;
}

void ATurpProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATurpProjectile::OnSphereOverlap);
}

void ATurpProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto GameState = Cast<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	if(OtherActor == TargetASC->GetAvatarActor())
	{
		UTurpAbilitySystemBlueprintFL::ApplyGameplayEffect(GameState, GameplayEffectParams);
		Destroy();
	}
}
