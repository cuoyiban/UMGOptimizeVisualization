// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Containers/Array.h"



class SUIOptimizeVisualizationLines : public SLeafWidget
{
public:

	SLATE_BEGIN_ARGS(SUIOptimizeVisualizationLines)
	{}
	SLATE_END_ARGS()


public:
	SUIOptimizeVisualizationLines();

	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
public:
	void SetPoint(FVector2D star, TArray<FVector2D> end , FVector2D& topleft, FVector2D& bottomright);
private:
	FVector2D m_vecStar;
	TArray<FVector2D> m_arrVecEnd;

	FVector2D m_boundSize;
};
