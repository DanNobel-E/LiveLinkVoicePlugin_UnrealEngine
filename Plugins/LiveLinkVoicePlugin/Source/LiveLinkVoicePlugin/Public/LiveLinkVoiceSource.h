// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "ILiveLinkSource.h"
#include "ILiveLinkClient.h"
#include "Interfaces/VoiceCapture.h"
#include "LiveLinkVoiceSourceSettings.h"
#include "Roles/LiveLinkAnimationRole.h"
#include "VoicePackage.h"
#include "VoiceModule.h"


class ULiveLinkVoiceSourceFactory;


class LIVELINKVOICEPLUGIN_API FLiveLinkVoiceSource : public ILiveLinkSource, public FTickableGameObject, public TSharedFromThis<FLiveLinkVoiceSource>
{
public:
	FLiveLinkVoiceSource(TSharedRef<class IVoiceCapture> InVoiceCapture, ULiveLinkVoiceSourceSettings* InSettings);
	~FLiveLinkVoiceSource();

	bool IsSourceStillValid() const override;

	void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;

	bool RequestSourceShutdown() override;

	FText GetSourceType() const override;

	FText GetSourceMachineName() const override;

	FText GetSourceStatus() const override;

	virtual void Tick(float DeltaTime) override;

	bool IsTickableInEditor() const override;

	TStatId GetStatId() const override;

	void StartCapture();

	void StopCapture();

	virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;

	virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;

	//virtual void OnSettingsChanged(ULiveLinkSourceSettings* Settings, const FPropertyChangedEvent& PropertyChangedEvent) {};


	FLiveLinkSubjectKey SubjectKey;


	ILiveLinkClient* LiveLinkClient;
	ULiveLinkVoiceSourceSettings* VoiceSettings;

	TSharedPtr<class IVoiceCapture> SourceVoiceCapture;
	TArray<uint8> VoiceBuffer;

	float VoiceCaptureTimer;
	float VoiceCaptureDuration;
	float VoiceCapturePrevDuration;
	float LastPitchValue;
};
