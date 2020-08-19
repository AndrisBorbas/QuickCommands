// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuickCommandsSettings.h"

UQuickCommandsSettings::UQuickCommandsSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SaveDirectoryS = FString("C:/Users/YOUR_USERNAME/Documents/Unreal Projects");
	FileNameS = FString("commands.txt");
}
