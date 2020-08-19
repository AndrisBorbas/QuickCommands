// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Layout/SScrollBox.h"

class FToolBarBuilder;
class FMenuBuilder;

class FQuickCommandsModule : public IModuleInterface {
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FString ButtonName;
	/*FString SaveDirectory;
	FString FileName;*/
	FString TextToSave;
	FString Commands;
	TCHAR Command;
	TArray<FString> ButtonNames;
	TArray<FString> CommandCollection;

private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);
	void CreateCommandList(TSharedRef<SScrollBox>, FString);
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
