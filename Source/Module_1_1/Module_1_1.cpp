// Fill out your copyright notice in the Description page of Project Settings.

#include "Module_1_1.h"
#include "Modules/ModuleManager.h"



DEFINE_LOG_CATEGORY(Module_1_1);

#define LOCTEXT_NAMESPACE "FTestModule"

void FModule_1_1::StartupModule()
{
	UE_LOG(Module_1_1, Warning, TEXT("Module_1_1 module has started!"));
}

void FModule_1_1::ShutdownModule()
{
	UE_LOG(Module_1_1, Warning, TEXT("Module_1_1 module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FModule_1_1, Module_1_1);
