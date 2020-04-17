// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomPlugin_WithWindowStyle.h"

class FCustomPlugin_WithWindowCommands : public TCommands<FCustomPlugin_WithWindowCommands>
{
public:

	FCustomPlugin_WithWindowCommands()
		: TCommands<FCustomPlugin_WithWindowCommands>(TEXT("CustomPlugin_WithWindow"), NSLOCTEXT("Contexts", "CustomPlugin_WithWindow", "CustomPlugin_WithWindow Plugin"), NAME_None, FCustomPlugin_WithWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};