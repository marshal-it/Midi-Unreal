// Copyright -> Scott Bishel

#include "ProceduralAudioPrivatePCH.h"
#include "SoundWaveProceduralTest.h"

USoundWaveProceduralTest::USoundWaveProceduralTest(const FObjectInitializer& PCIP)
	: Super(PCIP)
	, Time(0.0f)
	, Amplitude(8192.0f)
	, Frequency(100.0f)
{
	SampleRate = 44100;
	NumChannels = 2;
	Duration = INDEFINITELY_LOOPING_DURATION;
	bProcedural = true;
	bLooping = false;
	DeltaTime = 1.0f / SampleRate;    // time increment between samples [s]
	
}

int32 USoundWaveProceduralTest::GeneratePCMData(uint8* PCMData, const int32 SamplesNeeded)
{
	float TimeStart = Time;

	// Sine
	Omega = 2.0f * PI * Frequency;	// angular frequency [rad/s]
	// Saw
//	Omega = 2.0f * (1.0f / (SampleRate / Frequency));	// angular frequency [rad/s]

	for (int i = 0; i < SamplesNeeded; i++)
	{
		Time = TimeStart + i * DeltaTime;
		// Sine
		int32 a = Amplitude * FMath::Sin(Omega*Time);

		// Saw
/*		float val = data._phasor;
		data._phasor += Omega;
		if (data._phasor > data._tolerance) {
			data._phasor -= 2.0f;
		}
		int32 a = Amplitude * data._phasor;
*/
		if (a > MAX_uint16)
		{
			a = MAX_uint16;
		}
		else if (a < 0)
		{
			a = 0;
		}
		uint16 ua = (uint16)a;
		PCMData[2 * i] = ua;			// Low Byte
		PCMData[2 * i + 1] = ua >> 8;	// High Byte
	}

	Time = TimeStart + SamplesNeeded * DeltaTime;

	int32 BytesProvided = SamplesNeeded * 2;
	return BytesProvided;
}

SIZE_T USoundWaveProceduralTest::GetResourceSize(EResourceSizeMode::Type Mode)
{
	return 0;
}

int32 USoundWaveProceduralTest::GetResourceSizeForFormat(FName Format)
{
	return 0;
}

void USoundWaveProceduralTest::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
	// should never be in asset registry
	check(false);
}

FByteBulkData* USoundWaveProceduralTest::GetCompressedData(FName Format)
{
	return NULL;
}

void USoundWaveProceduralTest::Serialize(FArchive& Ar)
{
	// do not call the USoundWave version of serialize
	USoundBase::Serialize(Ar);
}

void USoundWaveProceduralTest::InitAudioResource(FByteBulkData& CompressedData)
{
	// should never be pushing compressed data
	check(false);
}

bool USoundWaveProceduralTest::InitAudioResource(FName Format)
{
	//nothing to be done to initialize
	return true;
}
