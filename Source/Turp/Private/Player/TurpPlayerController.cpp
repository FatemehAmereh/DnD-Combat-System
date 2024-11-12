// Copyright Erza.


#include "Player\TurpPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/TurpAbilitySystemBlueprintFL.h"
#include "AbilitySystem/TurpAbilitySystemComponent.h"
#include "Game/TurpGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void ATurpPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputMappingContext);
	if(	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATurpPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATurpPlayerController::Move);	
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Triggered, this, &ATurpPlayerController::AbilityActionTrigger);	
	}
}

void ATurpPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// determine forward direction using the controller
	const FRotator Rotation {0.0f, GetControlRotation().Yaw, 0.0f};
	FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	FVector RightdDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightdDirection, InputAxisVector.X);
	}
}

void ATurpPlayerController::AbilityActionTrigger()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	auto ASC = Cast<UTurpAbilitySystemComponent>(HitResult.GetActor()->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	auto GameState = CastChecked<ATurpGameStateBase>(UGameplayStatics::GetGameState(this));
	UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_TargetASC(GameState, ASC);
	UTurpAbilitySystemBlueprintFL::AddCombatPacketParam_TargetLocation(GameState, HitResult.Location);
	
	AbilityActionTriggered.Broadcast();
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, 	HitResult.GetActor()->GetName());
}
