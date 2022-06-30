// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ILiveLinkClient.h"
#include "LiveLinkComponentController.h"
#include "LiveLinkVoiceSource.h"
#include "LiveLinkSourceSettings.h"
#include "LiveLinkBlueprintLibrary.h"

#include "LiveLinkVoiceComponentController.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LIVELINKVOICEPLUGIN_API ULiveLinkVoiceComponentController : public ULiveLinkComponentController
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable, Category = "LiveLink")
		void StartVoiceCapture();

	UFUNCTION(BlueprintCallable, Category = "LiveLink")
		void StopVoiceCapture();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULiveLinkVoiceSourceSettings* SourceSettings;



};
