// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
// Code used created by Rens https://overview.artbyrens.com/commands.php

#include "QuickCommands.h"
#include "QuickCommandsStyle.h"
#include "QuickCommandsCommands.h"
#include "QuickCommandsSettings.h"

#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ISettingsModule.h"
#include "Misc/FileHelper.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SSeparator.h"

static const FName QuickCommandsTabName("QuickCommands");

#define LOCTEXT_NAMESPACE "FQuickCommandsModule"

void FQuickCommandsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FQuickCommandsStyle::Initialize();
	FQuickCommandsStyle::ReloadTextures();

	FQuickCommandsCommands::Register();

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Editor", "Plugins", "Quick Commands",
		                                 LOCTEXT("QuickCommandsName", "Quick Commands"),
		                                 LOCTEXT("QuickCommandsNameDesc",
		                                         "Configure options for the location of the commands file"),
		                                 GetMutableDefault<UQuickCommandsSettings>()
		);
	}

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuickCommandsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuickCommandsModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
		                               FMenuExtensionDelegate::CreateRaw(
			                               this, &FQuickCommandsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
		                                     FToolBarExtensionDelegate::CreateRaw(
			                                     this, &FQuickCommandsModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuickCommandsTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FQuickCommandsModule::OnSpawnPluginTab))
	                        .SetDisplayName(LOCTEXT("FQuickCommandsTabTitle", "QuickCommands"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuickCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		SettingsModule->UnregisterSettings("Editor", "Plugins", "QuickCommands");

	FQuickCommandsStyle::Shutdown();

	FQuickCommandsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuickCommandsTabName);
}

void FQuickCommandsModule::CreateCommandList(TSharedRef<SScrollBox> ButtonList, FString AbsoluteFilePath)
{
	ButtonList->ClearChildren();
	ButtonList->AddSlot()[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(3.0f, 4.0f, 3.0f, 4.0f)[
			SNew(SButton)
			.ButtonColorAndOpacity(FLinearColor(1, 1, 1, .9))[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(1.0f, 3.0f)[
					SNew(STextBlock)
					.Text(FText::FromString("Refresh List"))
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12))
					.Justification(ETextJustify::Center)
				]
			]
			.OnClicked_Lambda([this, ButtonList, AbsoluteFilePath]()-> FReply
			{
				CreateCommandList(ButtonList, AbsoluteFilePath);
				return FReply::Handled();
			})
		]
	];
	ButtonList->AddSlot()[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(3.0f, 4.0f)[
			SNew(SSeparator)
		]
	];

	CommandCollection.Empty();
	FFileHelper::LoadANSITextFileToStrings(*AbsoluteFilePath, nullptr, CommandCollection);
	for (const auto& ConsoleCommand : CommandCollection)
	{
		if (!ConsoleCommand.TrimStartAndEnd().IsEmpty())
		{
			ButtonList->AddSlot()[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(3.0f, 1.0f)[
					SNew(SButton)
					.ButtonColorAndOpacity(FLinearColor(1, 1, 1, .9))[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(1.0f, 3.0f)[
							SNew(STextBlock)
						.Text(FText::FromString(ConsoleCommand))
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 9))
						]
					]
					.OnClicked_Lambda([ConsoleCommand]()-> FReply
					{
						GEngine->Exec(GEngine->GetWorldContexts().Last().World(), *ConsoleCommand.TrimStartAndEnd(),
						              *GLog);
						return FReply::Handled();
					})
				]
			];
		}
		else
		{
			ButtonList->AddSlot()[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(3.0f, 3.0f)[
					SNew(SSeparator)
				]
			];
		}
	}
}

TSharedRef<SDockTab> FQuickCommandsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FString FileName = GetMutableDefault<UQuickCommandsSettings>()->ConfigFile.FilePath;
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FQuickCommandsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("QuickCommands.cpp"))
	);

	TSharedRef<SScrollBox> ButtonList = SNew(SScrollBox);

	CreateCommandList(ButtonList, FileName);

	return SNew(SDockTab)
		.TabRole(NomadTab)[
			ButtonList
		];
}

void FQuickCommandsModule::PluginButtonClicked() { FGlobalTabmanager::Get()->TryInvokeTab(QuickCommandsTabName); }

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
