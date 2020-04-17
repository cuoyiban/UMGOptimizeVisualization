// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UMGOptimizeTool.h"
#include "UMGOptimizeToolStyle.h"
#include "UMGOptimizeToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SUIOptimizeVisualizationTree.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/AssetManager.h"
#include "Blueprint/UserWidget.h"

static const FName UMGOptimizeToolTabName("UMGOptimizeTool");

#define LOCTEXT_NAMESPACE "FUMGOptimizeToolModule"

void FUMGOptimizeToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUMGOptimizeToolStyle::Initialize();
	FUMGOptimizeToolStyle::ReloadTextures();

	FUMGOptimizeToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUMGOptimizeToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FUMGOptimizeToolModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FUMGOptimizeToolModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FUMGOptimizeToolModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UMGOptimizeToolTabName, FOnSpawnTab::CreateRaw(this, &FUMGOptimizeToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FUMGOptimizeToolTabTitle", "UMGOptimizeTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FUMGOptimizeToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FUMGOptimizeToolStyle::Shutdown();

	FUMGOptimizeToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UMGOptimizeToolTabName);
}

TSharedRef<SDockTab> FUMGOptimizeToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FUMGOptimizeToolModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("UMGOptimizeTool.cpp"))
		);
	TSharedPtr<SUIOptimizeVisualizationTree> tree;
	TSharedPtr<SDockTab> temp;
	SAssignNew(temp , SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(tree , SUIOptimizeVisualizationTree).EntrySeparation(5).LayerSeparation(5)
				/*SNew(STextBlock)
				.Text(WidgetText)*/
			]
		];
	UClass* cl = LoadClass<UUserWidget>(nullptr, TEXT("BlueprintGeneratedClass'/Game/NewFolder/NewWidgetBlueprint.NewWidgetBlueprint_C'"));
	tree->GenerateFromUMG(Cast<UWidgetBlueprintGeneratedClass>(cl));


	return temp.ToSharedRef();
}

void FUMGOptimizeToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(UMGOptimizeToolTabName);
}

void FUMGOptimizeToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FUMGOptimizeToolCommands::Get().OpenPluginWindow);
}

void FUMGOptimizeToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FUMGOptimizeToolCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUMGOptimizeToolModule, UMGOptimizeTool)