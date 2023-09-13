#ifndef COMPONENT_AUDIOPLAYER2D_H
#define COMPONENT_AUDIOPLAYER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct AudioPlayer2D: public TComponent<AudioPlayer2D>
{
public:
	// resource name
	UniqueString AudioName;
	// audio resource
	ResourceID AudioID;

	// auto play on create
	bool AutoPlaying = false;

	// audio volume (Don't edit this field use Set / Get Volume)
	float Volume = 1.0f;

	// channels
	AudioChannelID ChannelID = CHUNK_NULL - 1;

	// on create override
	void OnCreate();

	// play audio by name
	void Play();

	// stop audio
	inline void Stop()
	{
		AudioEngine::Stop(ChannelID);
	}

	// is playing
	inline bool IsPlaying() const
	{
		return AudioEngine::IsPlaying(ChannelID);
	}

	// set volume
	inline void SetVolume(float newVolume)
	{
		Volume = newVolume;
		AudioEngine::SetVolume(ChannelID, Volume);
	}

	// get volume
	inline float GetVolume() const
	{
		return Volume;
	}

};

#endif // COMPONENT_AUDIOPLAYER2D_H