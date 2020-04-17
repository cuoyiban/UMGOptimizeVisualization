// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"



class SUIOptimizeVisualizationEntry : public SOverlay
{
public:

	SLATE_BEGIN_ARGS(SUIOptimizeVisualizationEntry)
		:_Layer(0) , _Batch(0) , _WidgetName(FText::FromString(TEXT("UNKNOW"))), _WidgetType(FText::FromString(TEXT("UNKNOW")))
	{}
	SLATE_ARGUMENT(int, Layer)
	SLATE_ARGUMENT(int, Batch)
	SLATE_ARGUMENT(FText, WidgetName)
	SLATE_ARGUMENT(FText, WidgetType)
	SLATE_END_ARGS()


public:
	SUIOptimizeVisualizationEntry();

	void Construct(const FArguments& InArgs);

public:
	void SetLayer(int iLayer);
	void SetBatch(int iBatch);

	void SetBatchHighlightState(int bHighlight);
	void SetLayerHighlightState(int bHighlight);

	FText GetInformationText();
private:
	int m_iLayer;
	int m_iBatch;
	TSharedPtr<STextBlock> m_textLayerAndBatch;
	TSharedPtr<STextBlock> m_textName;
	TSharedPtr<STextBlock> m_textType;
	
};
