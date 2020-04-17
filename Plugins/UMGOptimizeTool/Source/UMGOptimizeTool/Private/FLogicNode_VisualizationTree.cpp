#include "FLogicNode_VisualizationTree.h"
#include "UObject/Class.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"
#include "Blueprint/UserWidget.h"

FLogicNode_VisualizationTree::FLogicNode_VisualizationTree()
{
	m_iClass2TypeEnum.Add(UCanvasPanel::StaticClass(), EWidgetType::E_UCanvasPanel);
	m_iClass2TypeEnum.Add(UImage::StaticClass(), EWidgetType::E_UImage);
	m_iClass2TypeEnum.Add(UTextBlock::StaticClass(), EWidgetType::E_UText);
	m_iClass2TypeEnum.Add(UButton::StaticClass(), EWidgetType::E_UButton);
	m_iClass2TypeEnum.Add(UNamedSlot::StaticClass(), EWidgetType::E_UNameSlot);
	m_iClass2TypeEnum.Add(UUserWidget::StaticClass(), EWidgetType::E_UUserWidget);
}


void FLogicNode_VisualizationTree::AddChild(FLogicNode_VisualizationTree* childNode)
{
	m_arrChildren.Add(childNode);
}

void FLogicNode_VisualizationTree::SetWidget(UWidget* widget)
{
	/*UClass* class = widget->GetClass();
	if (class)*/
	m_textName = FText::FromString(widget->GetName());
	m_textType = FText::FromString(widget->GetClass()->GetName().Left(2));

}

