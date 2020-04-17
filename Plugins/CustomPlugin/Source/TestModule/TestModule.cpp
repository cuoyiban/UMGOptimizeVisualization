// Fill out your copyright notice in the Description page of Project Settings.

#include "TestModule.h"

//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, CustomPluginTest, "CustomPluginTest");

DEFINE_LOG_CATEGORY(TestModule);

#define LOCTEXT_NAMESPACE "FTestModule"

void FTestModule::StartupModule()
{
	UE_LOG(TestModule, Warning, TEXT("TestModule module has started!"));
}

void FTestModule::ShutdownModule()
{
	UE_LOG(TestModule, Warning, TEXT("TestModule module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestModule, TestModule)