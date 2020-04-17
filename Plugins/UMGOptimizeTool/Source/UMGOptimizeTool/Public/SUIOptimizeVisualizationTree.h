#pragma once

#include "CoreMinimal.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "SUIOptimizeVisualizationEntryAdapter.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/NamedSlot.h"
#include "FLogicNode_VisualizationTree.h"
#include "SUIOptimizeVisualizationLines.h"

//DECLARE_LOG_CATEGORY_EXTERN(SUIOptimizeVisualizationTree, All, All);

class SUIOptimizeVisualizationTree : public SConstraintCanvas
{
public:

	SLATE_BEGIN_ARGS(SUIOptimizeVisualizationTree)
		:_LayerSeparation(10) , _EntrySeparation(10)
	{}
	SLATE_ARGUMENT(int , LayerSeparation)
	SLATE_ARGUMENT(int , EntrySeparation)
	SLATE_END_ARGS()

	
public:
	SUIOptimizeVisualizationTree();

	void Construct(const FArguments& InArgs);

	void GenerateFromUMG(UWidgetBlueprintGeneratedClass *umgBlueprintGeneratedClass);
	void ParseFromUMG(UWidgetBlueprintGeneratedClass* umgBlueprintGeneratedClass);
	FLogicNode_VisualizationTree * RecursionParseUWidget(UWidget* widget , UUserWidget *ownerWidget);

	void GenerateTree();
	TSharedPtr<SUIOptimizeVisualizationEntryAdapter> GenerateFromLogicNodeRecursion(FLogicNode_VisualizationTree* logicNode);

	TSharedPtr<SUIOptimizeVisualizationEntryAdapter> RecursionGenerateFromWidgetTree(UWidgetTree* widgetTree , UWidget *currentWidget);

	void LayoutTree();
	void LayoutRecursion(SUIOptimizeVisualizationEntryAdapter* entryAdapter, FVector2D beginPosition);

	void ComputerLayerHeightRecursion(SUIOptimizeVisualizationEntryAdapter* currentAdapter , int iLayer);

private:
	TArray<UWidget*> GetChildWidgets(UWidget* parent, UUserWidget* owner = nullptr);

	void ComputerLayoutData();

private:
	TArray<SUIOptimizeVisualizationEntryAdapter*> m_AllVisualizationEntryAdapter;
	TMap<SUIOptimizeVisualizationEntryAdapter*, SConstraintCanvas::FSlot*> m_WidgetToSlot;

	SUIOptimizeVisualizationEntryAdapter* m_rootEntryAdapter;

	FLogicNode_VisualizationTree* m_rootLogicNode;

	TArray<SConstraintCanvas::FSlot*> m_arrLineSlots;

	TMap<int, int> m_mapLayerHeight;

	int m_iEntrySeparation;
	int m_iLayerSeparation;
};