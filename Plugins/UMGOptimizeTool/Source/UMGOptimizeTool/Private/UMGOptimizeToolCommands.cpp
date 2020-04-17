// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UMGOptimizeToolCommands.h"

#define LOCTEXT_NAMESPACE "FUMGOptimizeToolModule"

void FUMGOptimizeToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "UMGOptimizeTool", "Bring up UMGOptimizeTool window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
