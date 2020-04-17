#include "SUIOptimizeVisualizationTree.h"
#include "SUIOptimizeVisualizationEntry.h"

//DEFINE_LOG_CATEGORY(SUIOptimizeVisualizationTree);

#define LOCTEXT_NAMESPACE "SUIOptimizeVisualizationTree"

SUIOptimizeVisualizationTree::SUIOptimizeVisualizationTree()
{
	
}

void SUIOptimizeVisualizationTree::Construct(const FArguments& InArgs)
{
	m_iEntrySeparation = InArgs._EntrySeparation;
	m_iLayerSeparation = InArgs._LayerSeparation;
}

void SUIOptimizeVisualizationTree::GenerateFromUMG(UWidgetBlueprintGeneratedClass* umgBlueprintGeneratedClass)
{
	/*UWidgetTree* WidgetTree = umgBlueprintGeneratedClass->WidgetTree;
	TSharedPtr<SUIOptimizeVisualizationEntryAdapter> rootEntryAdapter = RecursionGenerateFromWidgetTree(WidgetTree, WidgetTree->RootWidget);
	m_rootEntryAdapter = rootEntryAdapter.Get();
	m_rootEntryAdapter->CacheSizeInTree();
	LayoutTree();*/

	ParseFromUMG(umgBlueprintGeneratedClass);
	GenerateTree();
}

TSharedPtr<SUIOptimizeVisualizationEntryAdapter> SUIOptimizeVisualizationTree::RecursionGenerateFromWidgetTree(UWidgetTree* widgetTree, UWidget* currentWidget)
{
	TSharedPtr<SUIOptimizeVisualizationEntryAdapter> currentWidgetAdapter;
	if (currentWidget == nullptr)
	{
		return currentWidgetAdapter;
	}
	
	
	FSlot& slot = AddSlot();
	slot
	[
		SAssignNew(currentWidgetAdapter, SUIOptimizeVisualizationEntryAdapter)
		[
			SNew(SUIOptimizeVisualizationEntry)
			.Layer(0)
			.Batch(0)
			.WidgetName(FText::FromString(currentWidget->GetName()))
			.WidgetType(FText::FromString(currentWidget->GetClass()->GetName()))
		].EntrySeparation(this->m_iEntrySeparation)
	]
	.Alignment(FVector2D(0, 0.5))
	.Anchors(FAnchors(0, 0.5, 0, 0.5))
	.AutoSize(true);

	m_WidgetToSlot.Add(currentWidgetAdapter.Get(), &slot);
	m_AllVisualizationEntryAdapter.Add(currentWidgetAdapter.Get());

	TArray<UWidget*> arrChildren = GetChildWidgets(currentWidget, nullptr);
	//widgetTree->GetChildWidgets(currentWidget, arrChildren);


	if (arrChildren.Num() != 0)
	{
		for (int i = 0; i < arrChildren.Num(); i++)
		{
			TSharedPtr<SUIOptimizeVisualizationEntryAdapter> childWidgetAdapter;
			childWidgetAdapter = RecursionGenerateFromWidgetTree(widgetTree, arrChildren[i]);
			if (childWidgetAdapter.IsValid())
			{
				currentWidgetAdapter->AddChild(childWidgetAdapter.Get());
			}
		}
	}
	return currentWidgetAdapter;

}

void SUIOptimizeVisualizationTree::LayoutTree()
{
	LayoutRecursion(m_rootEntryAdapter, FVector2D(0, 0));
}

void SUIOptimizeVisualizationTree::LayoutRecursion(SUIOptimizeVisualizationEntryAdapter* entryAdapter, FVector2D beginPosition)
{
	FSlot& slot = **(m_WidgetToSlot.Find(entryAdapter));
	FVector2D size = entryAdapter->GetSize();
	slot.Offset(FMargin(beginPosition.X, beginPosition.Y, size.X, size.Y));

	TArray<SUIOptimizeVisualizationEntryAdapter*> arrChildren = entryAdapter->GetChildrenInTree();

	int currentAdapterWidgetInTree = entryAdapter->GetSubTreeWidget();
	FVector2D childPosition(beginPosition.X + size.X + m_iLayerSeparation, beginPosition.Y - currentAdapterWidgetInTree / 2);
	TArray<FVector2D> arrEndPosition;
	for (int i = 0; i < arrChildren.Num(); i++)
	{
		int childTreeWidget = arrChildren[i]->GetSubTreeWidget();
		childPosition.Y = childPosition.Y + childTreeWidget / 2;
		LayoutRecursion(arrChildren[i], childPosition);
		arrEndPosition.Add(childPosition);
		childPosition.Y = childPosition.Y + childTreeWidget / 2 + m_iEntrySeparation;
	}

	if (arrEndPosition.Num() == 0)
	{
		return;
	}

	TSharedPtr<SUIOptimizeVisualizationLines> line;
	FSlot& lineSlot = AddSlot();
	lineSlot
	[
		SAssignNew(line, SUIOptimizeVisualizationLines)
	]
	.AutoSize(true)
	.Alignment(FVector2D(0, 0.5))
	.Anchors(FAnchors(0, 0.5, 0, 0.5));

	FVector2D topleft;
	FVector2D bottomright;
	line->SetPoint(
		FVector2D(beginPosition.X + size.X, beginPosition.Y),
		arrEndPosition,
		topleft,
		bottomright
	);
	lineSlot.Offset(
		FMargin(
			beginPosition.X + size.X, beginPosition.Y,
			bottomright.X - topleft.X, bottomright.Y - topleft.Y
		)
	);
	m_arrLineSlots.Add(&lineSlot);
}


TArray<UWidget*> SUIOptimizeVisualizationTree::GetChildWidgets(UWidget* parent, UUserWidget *ownerWidget)
{
	TArray<UWidget*> returnValue;

	//nameslot search
	if (UNamedSlot* nameSlot = Cast<UNamedSlot>(parent))
	{
		if (ownerWidget != nullptr)
		{
			UWidget* nameSlotContent = ownerWidget->GetContentForSlot(nameSlot->GetFName());
			if (nameSlotContent != nullptr)
			{
				returnValue.Add(nameSlotContent);
			}
		}
	}
	// Search standard children.
	else if (UPanelWidget* PanelParent = Cast<UPanelWidget>(parent))
	{
		for (int32 ChildIndex = 0; ChildIndex < PanelParent->GetChildrenCount(); ChildIndex++)
		{
			if (UWidget* ChildWidget = PanelParent->GetChildAt(ChildIndex))
			{
				returnValue.Add(ChildWidget);
			}
		}
	}
	
	
	//UMG UUserWidget	
	if (UUserWidget* PanelParent = Cast<UUserWidget>(parent))
	{
		if (UWidgetBlueprintGeneratedClass* blueprintClass = Cast<UWidgetBlueprintGeneratedClass>(PanelParent->GetClass()))
		{
			returnValue.Add(blueprintClass->WidgetTree->RootWidget);
		}
	}
	
	

	return returnValue;
}

void SUIOptimizeVisualizationTree::ParseFromUMG(UWidgetBlueprintGeneratedClass* umgBlueprintGeneratedClass)
{
	UWidgetTree* WidgetTree = umgBlueprintGeneratedClass->WidgetTree;
	m_rootLogicNode = RecursionParseUWidget(WidgetTree->RootWidget , nullptr);
}

FLogicNode_VisualizationTree* SUIOptimizeVisualizationTree::RecursionParseUWidget(UWidget* widget , UUserWidget* ownerWidget)
{
	if (widget == nullptr)
	{
		return nullptr;
	}

	FLogicNode_VisualizationTree* currentNode = new	FLogicNode_VisualizationTree();
	currentNode->SetWidget(widget);
	TArray<UWidget*> arrChildren = GetChildWidgets(widget, ownerWidget);
	
	if (arrChildren.Num() != 0)
	{
		if (widget->IsA(UUserWidget::StaticClass()))
		{
			ownerWidget = Cast<UUserWidget>(widget);
		}

		for (int i = 0; i < arrChildren.Num(); i++)
		{
			FLogicNode_VisualizationTree* childNode = RecursionParseUWidget(arrChildren[i] , ownerWidget);
			if (childNode != nullptr)
			{
				currentNode->AddChild(childNode);
			}
		}
	}
	return currentNode;
}


void SUIOptimizeVisualizationTree::GenerateTree()
{
	m_rootEntryAdapter = GenerateFromLogicNodeRecursion(m_rootLogicNode).Get();
	m_rootEntryAdapter->ComputerSubTreeWidget();
	LayoutTree();
}

TSharedPtr<SUIOptimizeVisualizationEntryAdapter> SUIOptimizeVisualizationTree::GenerateFromLogicNodeRecursion(FLogicNode_VisualizationTree* logicNode)
{
	TSharedPtr<SUIOptimizeVisualizationEntryAdapter> currentWidgetAdapter;

	FSlot& slot = AddSlot();
	slot
	[
		SAssignNew(currentWidgetAdapter, SUIOptimizeVisualizationEntryAdapter)
		[
			SNew(SUIOptimizeVisualizationEntry)
			.Layer(0)
			.Batch(0)
			.WidgetName(logicNode->GetName())
			.WidgetType(logicNode->GetType())
		]
		.EntrySeparation(this->m_iEntrySeparation)
	]
	.Alignment(FVector2D(0, 0.5))
	.Anchors(FAnchors(0, 0.5, 0, 0.5))
	.AutoSize(true);

	m_WidgetToSlot.Add(currentWidgetAdapter.Get(), &slot);
	m_AllVisualizationEntryAdapter.Add(currentWidgetAdapter.Get());


	TArray<FLogicNode_VisualizationTree*> allChildren = logicNode->GetChildren();
	for (int i = 0; i < allChildren.Num(); i++)
	{
		TSharedPtr<SUIOptimizeVisualizationEntryAdapter> childWidgetAdapter = GenerateFromLogicNodeRecursion(allChildren[i]);
		currentWidgetAdapter->AddChild(childWidgetAdapter.Get());
	}

	return currentWidgetAdapter;
}

void SUIOptimizeVisualizationTree::ComputerLayoutData()
{
	//subtrue widget
	m_rootEntryAdapter->ComputerSubTreeWidget();
	//layer height

}

void SUIOptimizeVisualizationTree::ComputerLayerHeightRecursion(SUIOptimizeVisualizationEntryAdapter* currentAdapter , int iLayer )
{

}

#undef LOCTEXT_NAMESPACE