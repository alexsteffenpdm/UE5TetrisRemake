// Copyright Epic Games, Inc. All Rights Reserved.

#include "TetrisGameMode.h"
#include "TetrisPlayerController.h"
#include "TetrisCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATetrisGameMode::ATetrisGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATetrisPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}