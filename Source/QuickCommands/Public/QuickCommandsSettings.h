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

	/** Location of the file */
	UPROPERTY(EditAnywhere, config, Category = Default)
	FString SaveDirectoryS;
	/** Name of the file */
	UPROPERTY(EditAnywhere, config, Category = Default)
	FString FileNameS;
};
