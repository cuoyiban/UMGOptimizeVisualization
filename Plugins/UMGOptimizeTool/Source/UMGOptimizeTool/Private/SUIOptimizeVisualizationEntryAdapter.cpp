#include "SUIOptimizeVisualizationEntryAdapter.h"
#include "Styling/SlateColor.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Images/SImage.h"
#include "Styling/SlateStyleRegistry.h"


void SUIOptimizeVisualizationEntryAdapter::Construct(const FArguments& InArgs)
{
	this->SetContent(InArgs._Content.Widget);
	this->ChildSlot.HAlign(EHorizontalAlignment::HAlign_Center).VAlign(EVerticalAlignment::VAlign_Center);
	this->m_iDir = InArgs._Dir;
	this->m_iEntrySeparation = InArgs._EntrySeparation;
}

SUIOptimizeVisualizationEntryAdapter::SUIOptimizeVisualizationEntryAdapter()
{
	
}

void SUIOptimizeVisualizationEntryAdapter::AddChild(SUIOptimizeVisualizationEntryAdapter* child)
{
	m_arrChildren.Add(child);
}
int SUIOptimizeVisualizationEntryAdapter::GetSubTreeWidget()
{
	return m_iSubTreeWidget;
}

int SUIOptimizeVisualizationEntryAdapter::ComputerSubTreeWidget()
{
	
	if (m_arrChildren.Num() == 0)
	{
		m_iSubTreeWidget = GetSize().Y;
	}
	else
	{
		for (int i = 0; i < m_arrChildren.Num(); i++)
		{
			m_iSubTreeWidget += m_arrChildren[i]->ComputerSubTreeWidget();
		}
		m_iSubTreeWidget += (m_arrChildren.Num() - 1) * m_iEntrySeparation;
	}
	return m_iSubTreeWidget;
}

FVector2D SUIOptimizeVisualizationEntryAdapter::GetSize()
{
	TSharedRef<SWidget> content = GetContent();
	
	content->SlatePrepass(content->GetTickSpaceGeometry().Scale);
	return FVector2D(300 , GetContent()->GetDesiredSize().Y);
	//return FVector2D(50, 50);
}