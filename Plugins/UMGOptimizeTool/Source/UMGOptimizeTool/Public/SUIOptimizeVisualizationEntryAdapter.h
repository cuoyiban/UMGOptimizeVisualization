// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Layout/SBorder.h"





class SUIOptimizeVisualizationEntryAdapter : public SBorder
{
public:

	SLATE_BEGIN_ARGS(SUIOptimizeVisualizationEntryAdapter)
		:_Content() , _Dir(0)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_ARGUMENT(int , Dir)
	SLATE_ARGUMENT(int, EntrySeparation)
	SLATE_END_ARGS()


public:
	SUIOptimizeVisualizationEntryAdapter();

	void Construct(const FArguments& InArgs);

	void AddChild(SUIOptimizeVisualizationEntryAdapter* child);
	int GetSubTreeWidget();
	int ComputerSubTreeWidget();
	FVector2D GetSize();

	TArray<SUIOptimizeVisualizationEntryAdapter*>& GetChildrenInTree() { return m_arrChildren; }
private:
	TArray<SUIOptimizeVisualizationEntryAdapter*> m_arrChildren;
	int m_iSubTreeWidget;
	int m_iDir;
	int m_iEntrySeparation;
};
