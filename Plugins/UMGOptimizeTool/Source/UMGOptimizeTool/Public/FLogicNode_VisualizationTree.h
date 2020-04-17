#pragma once

#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Components/Widget.h"
#include "Internationalization/Text.h"

enum class EAnalyzeType
{
	E_Static,
	E_Dynamic
};

enum class EWidgetType
{
	E_UImage,
	E_UText,
	E_UButton,
	E_UCanvasPanel,
	E_UUserWidget,
	E_UNameSlot,
};

struct FLogicNode_VisualizationTree
{
	FLogicNode_VisualizationTree();

	void AddChild(FLogicNode_VisualizationTree* childNode);
	void SetWidget(UWidget* widget);
	
	int Layer;
	int Batch;
	FText m_textName;
	FText m_textType;

	TArray<FLogicNode_VisualizationTree*> m_arrChildren;

	EWidgetType m_eWidgetType;
	EAnalyzeType m_eAnalyzeType;

public:
	FText GetName() { return m_textName; }
	FText GetType() { return m_textType; }
	TArray<FLogicNode_VisualizationTree*> GetChildren() { return m_arrChildren; }
	

private:
	TMap<UClass*, EWidgetType> m_iClass2TypeEnum;
};