// Copyright Epic Games, Inc. All Rights Reserved.

#include "BKGameMode.h"
#include "BKPlayerController.h"
#include "BKCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABKGameMode::ABKGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABKPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BK/Player/BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}