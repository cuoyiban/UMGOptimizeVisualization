// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomPlugin_WithWindow.h"
#include "CustomPlugin_WithWindowStyle.h"
#include "CustomPlugin_WithWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/AssetManager.h"
#include "Misc/MessageDialog.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName CustomPlugin_WithWindowTabName("CustomPlugin_WithWindow");

#define LOCTEXT_NAMESPACE "FCustomPlugin_WithWindowModule"

void FCustomPlugin_WithWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomPlugin_WithWindowStyle::Initialize();
	FCustomPlugin_WithWindowStyle::ReloadTextures();

	FCustomPlugin_WithWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomPlugin_WithWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomPlugin_WithWindowModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FCustomPlugin_WithWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FCustomPlugin_WithWindowModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomPlugin_WithWindowTabName, FOnSpawnTab::CreateRaw(this, &FCustomPlugin_WithWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCustomPlugin_WithWindowTabTitle", "CustomPlugin_WithWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCustomPlugin_WithWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FCustomPlugin_WithWindowStyle::Shutdown();

	FCustomPlugin_WithWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomPlugin_WithWindowTabName);
}

TSharedRef<SDockTab> FCustomPlugin_WithWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCustomPlugin_WithWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CustomPlugin_WithWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
			/*SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SSplitter).Orientation(EOrientation::Orient_Horizontal)
				+SSplitter::Slot()
				.Value(1)
				[
					SNew(STextBlock).Text(WidgetText)
				]
				+SSplitter::Slot().Value(2)
				[
					SNew(SButton)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					.Text(NSLOCTEXT("MediaPlayerEditor", "ApplyLabel", "Apply"))
					.OnClicked(this , &FCustomPlugin_WithWindowModule::OnUseSelected)
				]
			]*/
		];
}

void FCustomPlugin_WithWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(CustomPlugin_WithWindowTabName);
}

void FCustomPlugin_WithWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FCustomPlugin_WithWindowCommands::Get().OpenPluginWindow);
}

void FCustomPlugin_WithWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FCustomPlugin_WithWindowCommands::Get().OpenPluginWindow);
}

FReply FCustomPlugin_WithWindowModule::OnUseSelected()
{
	TArray<FAssetData> SelectedAssets;
	GEditor->GetContentBrowserSelections(SelectedAssets);

	for (const FAssetData& AssetData : SelectedAssets)
	{
		FPrimaryAssetId PrimaryAssetId = UAssetManager::Get().GetPrimaryAssetIdForData(AssetData);
		if (PrimaryAssetId.IsValid())
		{
			FString t1 = PrimaryAssetId.PrimaryAssetType.GetName().ToString();
			FString t2 = PrimaryAssetId.PrimaryAssetName.ToString();
			FText DialogText = FText::Format(
				LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
				FText::FromString(t1),
				FText::FromString(t2)
			);
			FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			return FReply::Handled();
		}
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomPlugin_WithWindowModule, CustomPlugin_WithWindow)