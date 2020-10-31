// Copyright Epic Games, Inc. All Rights Reserved.

#include "BKPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Player/PlayerPawn.h"

#include "Engine/World.h"

class APlayerPawn;

ABKPlayerController::ABKPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ABKPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &ABKPlayerController::Select);
	InputComponent->BindAction("Select", IE_Released, this, &ABKPlayerController::Deselect);

	InputComponent->BindAction("SetDestination",IE_Pressed, this, &ABKPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ABKPlayerController::OnSetDestinationReleased);
}

void ABKPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}	
}

void ABKPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ABKPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ABKPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
void ABKPlayerController::Select()
{	
	if(APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetPawn()))
	{
		FHitResult TraceHitResult;
		this->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector CursorFV = TraceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		//CursorToWorld->SetWorldLocation(TraceHitResult.Location);
		//CursorToWorld->SetWorldRotation(CursorR);
	}
}

void ABKPlayerController::Deselect()
{
}


