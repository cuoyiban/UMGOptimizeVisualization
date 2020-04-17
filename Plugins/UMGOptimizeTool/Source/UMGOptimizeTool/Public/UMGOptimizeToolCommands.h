// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UMGOptimizeToolStyle.h"

class FUMGOptimizeToolCommands : public TCommands<FUMGOptimizeToolCommands>
{
public:

	FUMGOptimizeToolCommands()
		: TCommands<FUMGOptimizeToolCommands>(TEXT("UMGOptimizeTool"), NSLOCTEXT("Contexts", "UMGOptimizeTool", "UMGOptimizeTool Plugin"), NAME_None, FUMGOptimizeToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};