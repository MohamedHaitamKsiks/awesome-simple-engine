#include "AudioExample.h"

void AudioExample::Init()
{
    // music comming from: https://opengameart.org/content/colossal-boss-battle-theme
    m_BossMainSource = AudioSource::GetResourceClass().Load("audios/boss_main.audio.json");
    m_PlayingID = AudioEngine::GetInstance().Play(m_BossMainSource, 1.0f, true);

    Renderer2D::GetInstance().GetOnRender2D().Connect([this](Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });
}

void AudioExample::OnRender2D(Renderer2D& renderer2D)
{
    if (!AudioEngine::GetInstance().IsPlaying(m_PlayingID))
        return;

    constexpr size_t rectangleCount = 320;

    float width = static_cast<float>(Display::GetInstance().GetWindowWidth());
    float height = static_cast<float>(Display::GetInstance().GetWindowHeight());

    for (size_t i = 0; i < rectangleCount; i ++)
    {
        size_t frameIndex = AudioEngine::GetInstance().GetCurrentFrameIndex(m_PlayingID);
        float value = m_BossMainSource->GetValue(frameIndex + i, 0);


        Vector2 rectSize(width / static_cast<float>(rectangleCount), height * value);
        Matrix3x3 rectTransform = Matrix3x3::Translate(Vector2(rectSize.x * static_cast<float>(i), height * (1.0f - value) * 0.5f));

        renderer2D.GetLayer("Default").DrawFillRectangle(rectSize, rectTransform, Color::WHITE());
    }
}

void AudioExample::OnInputEvent(const InputEvent& event)
{
    if (event.GetType() != InputEventType::KEYBOARD)
        return;

    const auto& keyEvent = event.Get<InputEventKeyboard>();
    if (!keyEvent.Pressed)
        return;

    // change volume
    if (keyEvent.Code == Keycode::KEY_UP)
        m_CurrentVolume += 0.1f;
    else if (keyEvent.Code == Keycode::KEY_DOWN)
        m_CurrentVolume -= 0.1f;

    if (m_CurrentVolume > 1.0f)
        m_CurrentVolume = 1.0f;
    else if (m_CurrentVolume < 0.0f)
        m_CurrentVolume = 0.0f;

    if (AudioEngine::GetInstance().IsPlaying(m_PlayingID))
        AudioEngine::GetInstance().SetVolume(m_PlayingID, m_CurrentVolume);

    // stop/play
    if (keyEvent.Code == Keycode::KEY_SPACE)
    {
        if (AudioEngine::GetInstance().IsPlaying(m_PlayingID))
        {
            AudioEngine::GetInstance().Stop(m_PlayingID);
            m_PlayingID = CHUNK_NULL;
        }
        else
        {
            m_PlayingID = AudioEngine::GetInstance().Play(m_BossMainSource, 1.0f, true);
        }
    }
}
