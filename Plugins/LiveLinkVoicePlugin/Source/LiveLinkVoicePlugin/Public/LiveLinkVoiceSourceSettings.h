// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "LiveLinkSourceSettings.h"
#include "Sound/SoundWaveProcedural.h"
#include "Components/AudioComponent.h"

#include "LiveLinkVoiceSourceSettings.generated.h"

class FLiveLinkVoiceSource;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LIVELINKVOICEPLUGIN_API ULiveLinkVoiceSourceSettings : public ULiveLinkSourceSettings
{
	GENERATED_BODY()
	
public: 

	ULiveLinkVoiceSourceSettings();

	void UpdatePitchCurve(const uint8* InVoiceBuffer, const uint32 BufferSize, const float InTime, const float DeltaTime);

	void ResetPitchCurve();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	TEnumAsByte<ERichCurveInterpMode> InterpolationMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	TEnumAsByte<ERichCurveTangentMode> TangentMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	float VolumeMultiplier;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	float SampleRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	int32 DefaultStepValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice Capture")
	float NormalizeValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voice Capture")
	UCurveFloat* PitchCurve;



	TSharedPtr<FLiveLinkVoiceSource> VoiceSource;

	float SampleTimer;


};
