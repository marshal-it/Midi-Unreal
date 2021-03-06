// Copyright -> Scott Bishel

#pragma once

#include "Sound/SoundWave.h"
#include "SoundWaveProceduralTest.generated.h"

//////////////////////////////////////////////////////////////////////////
/// USoundWaveProceduralTest :
///		A USoundWave that generates a single tone procedurally. This is
///		A test class that demonstrates the ability to create audio
///		procedurally (e.g. other algorithms could be used to generate
///		wind sounds etc.)
//////////////////////////////////////////////////////////////////////////
UCLASS()
class PROCEDURALAUDIO_API USoundWaveProceduralTest : public USoundWave
{
	GENERATED_UCLASS_BODY()
	
	float Amplitude;	// [Intensity]

	float Frequency;	// [Hz]

	// UObject interface

	virtual void Serialize(FArchive& Ar) override;
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	virtual SIZE_T GetResourceSize(EResourceSizeMode::Type Mode) override;

	// USoundWave interface

	virtual int32 GeneratePCMData(uint8* PCMData, const int32 SamplesNeeded) override;
	virtual int32 GetResourceSizeForFormat(FName Format) override;
	virtual FByteBulkData* GetCompressedData(FName Format) override;
	virtual void InitAudioResource(FByteBulkData& CompressedData) override;
	virtual bool InitAudioResource(FName Format) override;

private:



	// Mathmatical Saw Wave;
	typedef struct Saw_Data {
		double _phasor = 0.0;
		double _tolerance = 1.0;
	}Saw_Data;

	Saw_Data data;

	// Time of the last sample that was copied to the PCMData buffer [s]
	float Time;

	// Time between two consecutive samples in the audio signal [s]
	float DeltaTime;

	// Angular frequency of the single tone [rad/s]
	float Omega;
};
