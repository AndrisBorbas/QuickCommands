// Copyright 2018 fpwong, Inc. All Rights Reserved.

#include "QuickCommandsSettings.h"




UQuickCommandsSettings::UQuickCommandsSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SaveDirectoryS = FString("C:/Users/YOUR_USERNAME/Documents/Unreal Projects");
	FileNameS = FString("commands.txt");
}
