// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuickCommands.h"
#include "QuickCommandsStyle.h"
#include "QuickCommandsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "LevelEditor.h"
#include "Engine.h"

static const FName QuickCommandsTabName("QuickCommands");

#define LOCTEXT_NAMESPACE "FQuickCommandsModule"

void FQuickCommandsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuickCommandsStyle::Initialize();
	FQuickCommandsStyle::ReloadTextures();

	FQuickCommandsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuickCommandsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuickCommandsModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FQuickCommandsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FQuickCommandsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuickCommandsTabName, FOnSpawnTab::CreateRaw(this, &FQuickCommandsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FQuickCommandsTabTitle", "QuickCommands"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuickCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FQuickCommandsStyle::Shutdown();

	FQuickCommandsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuickCommandsTabName);
}

TSharedRef<SDockTab> FQuickCommandsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FQuickCommandsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("QuickCommands.cpp"))
		);

	TSharedRef< SScrollBox > ButtonList = SNew(SScrollBox);


	FString SaveDirectory = FString("D:/Projects/Uprojects");
	FString FileName = FString("commands.txt");
	FString TextToSave = Commands;
	FString AbsoluteFilePath = SaveDirectory + "/" + FileName;

	TArray< FString > CommandCollection;
	CommandCollection.Empty();
	FFileHelper::LoadANSITextFileToStrings(*AbsoluteFilePath, NULL, CommandCollection);
	for (const auto& ConsoleCommand : CommandCollection)
	{

		ButtonList->AddSlot()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(3.0f, 1.0f)
			[
				SNew(SButton)
				.ButtonColorAndOpacity(FLinearColor(1, 1, 1, .9))
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(1.0f, 3.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(ConsoleCommand))
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 9))
					]
				]
				.OnClicked_Lambda([ConsoleCommand]()->FReply { GEngine->Exec(NULL, *ConsoleCommand, *GLog);	return FReply::Handled(); })
			]
		];
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)

		[
			ButtonList
		];
}

void FQuickCommandsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(QuickCommandsTabName);
}

void FQuickCommandsModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FQuickCommandsCommands::Get().OpenPluginWindow);
}

void FQuickCommandsModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FQuickCommandsCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuickCommandsModule, QuickCommands)