// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkVoiceSettingsFactory.h"

ULiveLinkVoiceSettingsFactory::ULiveLinkVoiceSettingsFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = false;
	SupportedClass = ULiveLinkVoiceSourceSettings::StaticClass();

}


UObject* ULiveLinkVoiceSettingsFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();


	FString BasePath = TEXT("/Game/") + InName.ToString();
	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(BasePath, TEXT(""), PackageName, Name);
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
	FString LongPackageName = FPackageName::FilenameToLongPackageName(Name);
	if (FPackageName::DoesPackageExist(PackageName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't create preset"));
		return nullptr;
	}

	UPackage* Package = CreatePackage(*PackageName);
	ULiveLinkVoiceSourceSettings* Settings = NewObject<ULiveLinkVoiceSourceSettings>(Package, *Name, EObjectFlags::RF_Standalone | EObjectFlags::RF_Public);
	
	AssetRegistry.AssetCreated(Settings);
	Settings->AddToRoot();

	FString AssetPath = FString::Printf(TEXT("%s%s%s"), *FPaths::ProjectContentDir(), *Settings->GetName(), *FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = EObjectFlags::RF_Standalone | EObjectFlags::RF_Public;


	bool bResult = UPackage::SavePackage(Package, Settings, *AssetPath, SaveArgs);
	Settings->MarkPackageDirty();


	return Settings;


}