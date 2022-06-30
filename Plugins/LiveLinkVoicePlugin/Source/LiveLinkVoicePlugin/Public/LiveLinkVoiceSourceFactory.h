// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LiveLinkSourceFactory.h"
#include "LiveLinkVoiceSource.h"
#include "LiveLinkVoiceSettingsFactory.h"
#include "VoiceModule.h"
#include "Interfaces/VoiceCapture.h"
#include "LiveLinkVoiceSourceFactory.generated.h"

/**
 * 
 */
UCLASS()
class LIVELINKVOICEPLUGIN_API ULiveLinkVoiceSourceFactory : public ULiveLinkSourceFactory
{
	GENERATED_BODY()

public:

	virtual FText GetSourceDisplayName() const;

	virtual FText GetSourceTooltip() const;

	virtual ULiveLinkSourceFactory::EMenuType GetMenuType() const;

	TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const;
	
};
