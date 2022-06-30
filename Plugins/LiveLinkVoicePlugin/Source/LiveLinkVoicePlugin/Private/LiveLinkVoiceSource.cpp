// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkVoiceSource.h"

FLiveLinkVoiceSource::FLiveLinkVoiceSource(TSharedRef<class IVoiceCapture> InVoiceCapture, ULiveLinkVoiceSourceSettings* InSettings)
{
	LiveLinkClient = nullptr;
	SourceVoiceCapture = InVoiceCapture;
	VoiceSettings = InSettings;
	VoiceCaptureTimer = 0.f;
	VoiceCaptureDuration = 0.f;
	VoiceCapturePrevDuration = 0.f;
	LastPitchValue = 0.f;


}

FLiveLinkVoiceSource::~FLiveLinkVoiceSource()
{
	if (SourceVoiceCapture.IsValid())
	{
		StopCapture();
		SourceVoiceCapture.Reset();

	}

	LiveLinkClient = nullptr;
}

bool FLiveLinkVoiceSource::IsSourceStillValid() const
{
	return SourceVoiceCapture->IsCapturing();
}

void FLiveLinkVoiceSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
	LiveLinkClient = InClient;
	LiveLinkClient->AddSource(SharedThis(this));

	SubjectKey.SubjectName = FLiveLinkSubjectName(TEXT("Voice Recorder"));
	SubjectKey.Source = InSourceGuid;

	FLiveLinkStaticDataStruct StaticData;
	StaticData.InitializeWith(FLiveLinkBaseStaticData::StaticStruct(), nullptr);
	FLiveLinkBaseStaticData* BasicDataPtr = StaticData.Cast<FLiveLinkBaseStaticData>();
	BasicDataPtr->PropertyNames.Add("Duration");
	BasicDataPtr->PropertyNames.Add("Volume");
	BasicDataPtr->PropertyNames.Add("Pitch");




	InClient->PushSubjectStaticData_AnyThread(SubjectKey, ULiveLinkBasicRole::StaticClass(), MoveTemp(StaticData));


	InitializeSettings(VoiceSettings);

}


bool FLiveLinkVoiceSource::RequestSourceShutdown()
{

	if (SourceVoiceCapture.IsValid())
	{
		StopCapture();
		SourceVoiceCapture.Reset();

	}
	LiveLinkClient = nullptr;
	return true;
}

FText FLiveLinkVoiceSource::GetSourceType() const
{
	return FText::FromString("LiveLink Voice Source");
}

FText FLiveLinkVoiceSource::GetSourceMachineName() const
{
	return FText::FromString(FPlatformProcess::ComputerName());

}

FText FLiveLinkVoiceSource::GetSourceStatus() const
{
	FString Status = SourceVoiceCapture->IsCapturing() ? "Capturing" : "Waiting";
	return FText::FromString(Status);

}

void FLiveLinkVoiceSource::Tick(float DeltaTime)
{
	

	if (LiveLinkClient)
	{
		

		if (SourceVoiceCapture->IsCapturing())
		{

			VoiceCapturePrevDuration = VoiceCaptureDuration;
			VoiceCaptureTimer += DeltaTime;
			VoiceCaptureDuration = VoiceCaptureTimer;
			FLiveLinkFrameDataStruct FrameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkBaseFrameData::StaticStruct());
			FLiveLinkBaseFrameData* BaseFrameData = FrameDataStruct.Cast<FLiveLinkBaseFrameData>();
			BaseFrameData->WorldTime = FPlatformTime::Seconds();
			
			BaseFrameData->PropertyValues.Add(VoiceCaptureDuration);
			BaseFrameData->PropertyValues.Add(SourceVoiceCapture->GetCurrentAmplitude()* VoiceSettings->VolumeMultiplier);


			VoiceSettings->SampleTimer += DeltaTime;

			if (VoiceSettings->SampleTimer >= VoiceSettings->SampleRate)
			{
				VoiceSettings->SampleTimer = 0.f;


				uint32 AvailableDataBytes;
				uint32 ReadBytes;
				EVoiceCaptureState::Type State = SourceVoiceCapture->GetCaptureState(AvailableDataBytes);
				TArray<uint8> Buffer;

				if (State == EVoiceCaptureState::Ok && AvailableDataBytes > 0)
				{

					Buffer.SetNumUninitialized(AvailableDataBytes);
					SourceVoiceCapture->GetVoiceData(Buffer.GetData(), AvailableDataBytes, ReadBytes);
					VoiceSettings->UpdatePitchCurve(Buffer.GetData(), ReadBytes, VoiceCaptureTimer, VoiceSettings->SampleRate);


				}

				float CurrentPitch = LastPitchValue;
				if (VoiceSettings->PitchCurve)
				{
					LastPitchValue = VoiceSettings->PitchCurve->FloatCurve.Eval(VoiceCaptureTimer);

				}

			}

			
			BaseFrameData->PropertyValues.Add(LastPitchValue);



			LiveLinkClient->PushSubjectFrameData_AnyThread(SubjectKey, MoveTemp(FrameDataStruct));

		}
	}

}



bool FLiveLinkVoiceSource::IsTickableInEditor() const
{
	return true;
}


TStatId FLiveLinkVoiceSource::GetStatId() const
{
	return TStatId();
}



void FLiveLinkVoiceSource::StartCapture()
{
	if (!SourceVoiceCapture->IsCapturing())
	{
		VoiceCaptureTimer = 0.f;
		VoiceCapturePrevDuration = 0.f;
		VoiceCaptureDuration = 0.f;
		LastPitchValue = 0.f;
		VoiceSettings->ResetPitchCurve();
		SourceVoiceCapture->Start();

	}
}

void FLiveLinkVoiceSource::StopCapture()
{
	if (SourceVoiceCapture->IsCapturing())
	{
		VoiceCaptureDuration = VoiceCaptureTimer;
		VoiceSettings->PitchCurve->FloatCurve.AddKey(VoiceCaptureDuration, 0);
		SourceVoiceCapture->Stop();
	}

}

void FLiveLinkVoiceSource::InitializeSettings(ULiveLinkSourceSettings* Settings)
{
	ULiveLinkVoiceSourceSettings* InSettings = Cast<ULiveLinkVoiceSourceSettings>(Settings);
	
	InSettings->Factory = ULiveLinkSourceFactory::StaticClass();
	InSettings->VoiceSource = SharedThis(this);


}

TSubclassOf<ULiveLinkSourceSettings> FLiveLinkVoiceSource::GetSettingsClass() const
{

	return ULiveLinkVoiceSourceSettings::StaticClass();

}


