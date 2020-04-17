#include "SUIOptimizeVisualizationLines.h"


SUIOptimizeVisualizationLines::SUIOptimizeVisualizationLines()
{

}

void SUIOptimizeVisualizationLines::Construct(const FArguments& InArgs)
{

}

void SUIOptimizeVisualizationLines::SetPoint(FVector2D star, TArray<FVector2D> end , FVector2D& topleft , FVector2D& bottomright)
{
	TArray<FVector2D> temp;
	temp.Add(star);
	temp.Append(end);

	topleft = temp[0];
	bottomright = temp[0];
	for (int i = 0; i < temp.Num(); i++)
	{
		if (temp[i].X < topleft.X)
		{
			topleft.X = temp[i].X;
		}
		else if(temp[i].X > bottomright.X)
		{
			bottomright.X = temp[i].X;
		}

		if (temp[i].Y < topleft.Y)
		{
			topleft.Y = temp[i].Y;
		}
		else if(temp[i].Y > bottomright.Y)
		{
			bottomright.Y = temp[i].Y;
		}
	}


	m_vecStar = FVector2D(star.X - topleft.X, star.Y - topleft.Y);
	for (int i = 0; i < end.Num(); i++)
	{
		m_arrVecEnd.Add(FVector2D(end[i].X - topleft.X, end[i].Y - topleft.Y));
	}
	
	m_boundSize = FVector2D(bottomright.X - topleft.X, bottomright.Y - topleft.Y);
}

int32 SUIOptimizeVisualizationLines::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	for (int i = 0; i < m_arrVecEnd.Num(); i++)
	{
		TArray<FVector2D> temp;
		temp.Add(m_vecStar);
		temp.Add(m_arrVecEnd[i]);
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			temp,
			ESlateDrawEffect::None,
			FLinearColor::White
		);
	}
	
	return LayerId;
}

FVector2D SUIOptimizeVisualizationLines::ComputeDesiredSize(float) const
{
	return m_boundSize;
}