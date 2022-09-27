// Copyright Epic Games, Inc. All Rights Reserved.

#include "Side_v1GameMode.h"
#include "../Characters/Side_v1Character.h"
#include "UObject/ConstructorHelpers.h"

ASide_v1GameMode::ASide_v1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
