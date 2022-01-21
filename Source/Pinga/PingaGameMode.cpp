// Copyright Epic Games, Inc. All Rights Reserved.

#include "PingaGameMode.h"
#include "PingaCharacter.h"
#include "UObject/ConstructorHelpers.h"

APingaGameMode::APingaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
