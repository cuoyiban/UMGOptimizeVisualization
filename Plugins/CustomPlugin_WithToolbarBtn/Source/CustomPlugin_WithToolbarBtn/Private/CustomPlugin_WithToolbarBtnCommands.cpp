// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomPlugin_WithToolbarBtnCommands.h"

#define LOCTEXT_NAMESPACE "FCustomPlugin_WithToolbarBtnModule"

void FCustomPlugin_WithToolbarBtnCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "CustomPlugin_WithToolbarBtn", "Execute CustomPlugin_WithToolbarBtn action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
