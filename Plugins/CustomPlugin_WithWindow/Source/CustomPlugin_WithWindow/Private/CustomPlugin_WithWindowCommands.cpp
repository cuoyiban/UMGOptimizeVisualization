// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomPlugin_WithWindowCommands.h"

#define LOCTEXT_NAMESPACE "FCustomPlugin_WithWindowModule"

void FCustomPlugin_WithWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomPlugin_WithWindow", "Bring up CustomPlugin_WithWindow window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
