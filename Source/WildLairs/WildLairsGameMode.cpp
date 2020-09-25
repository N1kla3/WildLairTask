// Copyright Epic Games, Inc. All Rights Reserved.

#include "WildLairsGameMode.h"
#include "WildLairsPlayerController.h"
#include "WildLairsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWildLairsGameMode::AWildLairsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWildLairsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}