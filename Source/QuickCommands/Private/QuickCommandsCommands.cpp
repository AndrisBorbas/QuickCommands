// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuickCommandsCommands.h"

#define LOCTEXT_NAMESPACE "FQuickCommandsModule"

void FQuickCommandsCommands::RegisterCommands() {
	UI_COMMAND(OpenPluginWindow, "QuickCommands", "Bring up QuickCommands window", EUserInterfaceActionType::Button,
				FInputChord());
}

#undef LOCTEXT_NAMESPACE
