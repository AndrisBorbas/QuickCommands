// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuickCommandsSettings.h"

#include "Interfaces/IPluginManager.h"

UQuickCommandsSettings::UQuickCommandsSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConfigFile.FilePath = IPluginManager::Get().FindPlugin("QuickCommands")->GetBaseDir() / TEXT("Commands/commands.txt");
}
