// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkVoiceSourceSettings.h"

ULiveLinkVoiceSourceSettings::ULiveLinkVoiceSourceSettings()
{

	PitchCurve = NewObject<UCurveFloat>();
	VolumeMultiplier = 1.f;
	SampleRate = 0.5f;
	SampleTimer = SampleRate;
	DefaultStepValue = 1.f;
	NormalizeValue = 100.f;
	InterpolationMode = ERichCurveInterpMode::RCIM_Linear;
	TangentMode = ERichCurveTangentMode::RCTM_User;
}



void ULiveLinkVoiceSourceSettings::UpdatePitchCurve(const uint8* InVoiceBuffer, const uint32 BufferSize, const float InTime, const float DeltaTime)
{
	if (BufferSize > 0)
	{
		float Time = InTime - DeltaTime;
		uint32 TrueSize = BufferSize;
		float TimeStep = DeltaTime / TrueSize;
		int32 StepValue = FMath::Abs(DefaultStepValue);


		if (PitchCurve)
		{

			for (uint32 i = 0; i < TrueSize; i += StepValue)
			{
				FKeyHandle KeyHandle= PitchCurve->FloatCurve.AddKey(Time, InVoiceBuffer[i]/NormalizeValue);
				PitchCurve->FloatCurve.SetKeyInterpMode(KeyHandle, InterpolationMode);
				PitchCurve->FloatCurve.SetKeyTangentMode(KeyHandle, TangentMode);

				Time += TimeStep * StepValue;

			}


			PitchCurve->FloatCurve.AddKey(InTime, InVoiceBuffer[TrueSize - 1]/NormalizeValue);


		}

	}

}


void ULiveLinkVoiceSourceSettings::ResetPitchCurve()
{
	SampleTimer = SampleRate;
	if (PitchCurve)
	{
		PitchCurve->FloatCurve.AddKey(0, 0);
		PitchCurve->FloatCurve.Reset();

	}

}