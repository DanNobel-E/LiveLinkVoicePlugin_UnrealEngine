// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkVoiceComponentController.h"



void ULiveLinkVoiceComponentController::StartVoiceCapture()
{
	if (SourceSettings)
	{

		if (SourceSettings->VoiceSource.IsValid())
		{
			SourceSettings->VoiceSource->StartCapture();
		}

	}
}

void ULiveLinkVoiceComponentController::StopVoiceCapture()
{
	if (SourceSettings)
	{

		if (SourceSettings->VoiceSource.IsValid())
		{
			SourceSettings->VoiceSource->StopCapture();
		}

	}
}