// Copyright Epic Games, Inc. All Rights Reserved.

#include "AITestTaskGameMode.h"
#include "AITestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAITestTaskGameMode::AAITestTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/AiTestTask/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
