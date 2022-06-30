// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "LiveLinkVoiceSourceSettings.h"

#include "LiveLinkVoiceSettingsFactory.generated.h"


/**
 * 
 */
UCLASS()
class LIVELINKVOICEPLUGIN_API ULiveLinkVoiceSettingsFactory : public UFactory
{
	GENERATED_BODY()

public:

	ULiveLinkVoiceSettingsFactory(const FObjectInitializer& ObjectInitializer);

	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

	
};
