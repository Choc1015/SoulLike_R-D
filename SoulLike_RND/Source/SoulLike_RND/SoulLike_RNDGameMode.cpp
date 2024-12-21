// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulLike_RNDGameMode.h"
#include "SoulLike_RNDCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoulLike_RNDGameMode::ASoulLike_RNDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
