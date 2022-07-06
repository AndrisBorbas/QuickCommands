// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuickCommandsStyle.h"

class FQuickCommandsCommands : public TCommands<FQuickCommandsCommands>
{
public:
	FQuickCommandsCommands()
		: TCommands<FQuickCommandsCommands>(
			TEXT("QuickCommands"), NSLOCTEXT("Contexts", "QuickCommands", "QuickCommands Plugin"),
			NAME_None, FQuickCommandsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
