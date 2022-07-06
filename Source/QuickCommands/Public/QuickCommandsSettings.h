// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuickCommandsSettings.generated.h"

UCLASS(config = QuickCommands, defaultconfig)
class QUICKCOMMANDS_API UQuickCommandsSettings : public UObject
{
	GENERATED_BODY()

public:
	UQuickCommandsSettings(const FObjectInitializer& ObjectInitializer);

	/** Config file with its absolute location */
	UPROPERTY(EditAnywhere, config, Category = Default)
	FFilePath ConfigFile;
};
