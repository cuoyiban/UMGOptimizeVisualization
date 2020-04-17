// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomPlugin_WithToolbarBtn.h"
#include "CustomPlugin_WithToolbarBtnStyle.h"
#include "CustomPlugin_WithToolbarBtnCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"

static const FName CustomPlugin_WithToolbarBtnTabName("CustomPlugin_WithToolbarBtn");

#define LOCTEXT_NAMESPACE "FCustomPlugin_WithToolbarBtnModule"

void FCustomPlugin_WithToolbarBtnModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomPlugin_WithToolbarBtnStyle::Initialize();
	FCustomPlugin_WithToolbarBtnStyle::ReloadTextures();

	FCustomPlugin_WithToolbarBtnCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomPlugin_WithToolbarBtnCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FCustomPlugin_WithToolbarBtnModule::PluginButtonClicked),
		FCanExecuteAction());

	
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FCustomPlugin_WithToolbarBtnModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FCustomPlugin_WithToolbarBtnModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

}

void FCustomPlugin_WithToolbarBtnModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FCustomPlugin_WithToolbarBtnStyle::Shutdown();

	FCustomPlugin_WithToolbarBtnCommands::Unregister();
}

void FCustomPlugin_WithToolbarBtnModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FCustomPlugin_WithToolbarBtnModule::PluginButtonClicked()")),
							FText::FromString(TEXT("CustomPlugin_WithToolbarBtn.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FCustomPlugin_WithToolbarBtnModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FCustomPlugin_WithToolbarBtnCommands::Get().PluginAction);
}

void FCustomPlugin_WithToolbarBtnModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FCustomPlugin_WithToolbarBtnCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomPlugin_WithToolbarBtnModule, CustomPlugin_WithToolbarBtn)