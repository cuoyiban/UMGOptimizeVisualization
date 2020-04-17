// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomPlugin_WithToolbarBtnStyle.h"

class FCustomPlugin_WithToolbarBtnCommands : public TCommands<FCustomPlugin_WithToolbarBtnCommands>
{
public:

	FCustomPlugin_WithToolbarBtnCommands()
		: TCommands<FCustomPlugin_WithToolbarBtnCommands>(TEXT("CustomPlugin_WithToolbarBtn"), NSLOCTEXT("Contexts", "CustomPlugin_WithToolbarBtn", "CustomPlugin_WithToolbarBtn Plugin"), NAME_None, FCustomPlugin_WithToolbarBtnStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
