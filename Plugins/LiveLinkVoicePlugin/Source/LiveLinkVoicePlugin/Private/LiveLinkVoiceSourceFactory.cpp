// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkVoiceSourceFactory.h"


FText ULiveLinkVoiceSourceFactory::GetSourceDisplayName() const
{
	return FText::FromString("Voice Source");
}

FText ULiveLinkVoiceSourceFactory::GetSourceTooltip() const
{
	return FText::FromString("Add a Voice Source linked to the system default audio capture source");
}


ULiveLinkSourceFactory::EMenuType ULiveLinkVoiceSourceFactory::GetMenuType() const
{
	return EMenuType::MenuEntry;
}

TSharedPtr<ILiveLinkSource> ULiveLinkVoiceSourceFactory::CreateSource(const FString& ConnectionString) const
{
	
	TSharedPtr<class IVoiceCapture> VoiceCapture = FVoiceModule::Get().CreateVoiceCapture("");

	if (VoiceCapture.IsValid())
	{
		ULiveLinkVoiceSettingsFactory* SettingsFactory = NewObject< ULiveLinkVoiceSettingsFactory>();
		UObject* Settings =  SettingsFactory->FactoryCreateNew(ULiveLinkVoiceSourceSettings::StaticClass(), 
			nullptr, TEXT("NewSettings"), 
			EObjectFlags::RF_Standalone | EObjectFlags::RF_Public, 
			nullptr, GWarn, TEXT(""));

		TSharedPtr<FLiveLinkVoiceSource> VoiceSource = MakeShared<FLiveLinkVoiceSource>(VoiceCapture.ToSharedRef(), Cast<ULiveLinkVoiceSourceSettings>(Settings));

		return VoiceSource;

	}

	return nullptr;
}