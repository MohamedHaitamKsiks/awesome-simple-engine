#ifndef __SYSTEM_AUDIOEXAMPLE_H
#define __SYSTEM_AUDIOEXAMPLE_H

#include "ASEngine.h"
using namespace ASEngine;

class AudioExample: public ISystem
{
private:
    void Init() override;
    void OnRender2D(Renderer2D& renderer2D);
    void OnInputEvent(const InputEvent& event) override;

    AudioPlayingID m_PlayingID = CHUNK_NULL;
    float m_CurrentVolume = 1.0f;
    ResourceRef<AudioSource> m_BossMainSource{};
};

#endif // __SYSTEM_AUDIOEXAMPLE_H
