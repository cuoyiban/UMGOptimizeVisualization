#include "SUIOptimizeVisualizationEntry.h"
#include "Styling/SlateColor.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/SlateStyleRegistry.h"


void SUIOptimizeVisualizationEntry::Construct(const FArguments& InArgs)
{
	SetLayer(InArgs._Layer);
	SetBatch(InArgs._Batch);

	FSlateBrush *backGroundBrush = FCoreStyle::Get().GetDefaultBrush();
	const ISlateStyle* slateStyleSet =  FSlateStyleRegistry::FindSlateStyle("UMGOptimizeToolStyle");
	FOverlaySlot& backGroundSlot = AddSlot(0);
	FOverlaySlot& informationSlot = AddSlot(1);

	backGroundSlot
	[
		SNew(SImage).Image(slateStyleSet->GetBrush("EntryBG"))
	]
	.HAlign(EHorizontalAlignment::HAlign_Fill)
	.VAlign(EVerticalAlignment::VAlign_Fill);

	
	informationSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[
			//layer and batch
			SAssignNew(m_textLayerAndBatch , STextBlock).Text(GetInformationText())
		]
		+ SVerticalBox::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[
			//layer and batch
			SAssignNew(m_textName, STextBlock).Text(InArgs._WidgetName)
		]
		+ SVerticalBox::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[
			//layer and batch
			SAssignNew(m_textType, STextBlock).Text(InArgs._WidgetType)
		]
	]
	.HAlign(EHorizontalAlignment::HAlign_Left)
	.VAlign(EVerticalAlignment::VAlign_Top);
}

SUIOptimizeVisualizationEntry::SUIOptimizeVisualizationEntry()
{
	
}

void SUIOptimizeVisualizationEntry::SetLayer(int iLayer)
{
	m_iLayer = iLayer;
}

void SUIOptimizeVisualizationEntry::SetBatch(int iBatch)
{
	m_iLayer = iBatch;
}

void SUIOptimizeVisualizationEntry::SetBatchHighlightState(int bHighlight)
{

}
void SUIOptimizeVisualizationEntry::SetLayerHighlightState(int bHighlight)
{

}

FText SUIOptimizeVisualizationEntry::GetInformationText()
{
	return FText::Format(
		FTextFormat::FromString("L:{0} - B:{1}"),
		FText::FromString(FString::FromInt(m_iLayer)),
		FText::FromString(FString::FromInt(m_iBatch)));
}
