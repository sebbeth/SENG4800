// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HVCCC2GameMode.h"
#include "HVCCC2Pawn.h"

AHVCCC2GameMode::AHVCCC2GameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AHVCCC2Pawn::StaticClass();
}
