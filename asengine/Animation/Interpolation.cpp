#include "Interpolation.h"
#include "Core/Math/Math.h"

namespace ASEngine
{
    float Interpolation::FloatQuadEaseIn(float t)
    {
        return Math::Pow(t, 2.0f);
    }

    float Interpolation::FloatQuadEaseOut(float t)
    {
        return 1.0f -  Math::Pow(1.0f - t, 2.0f);;
    }

    float Interpolation::FloatQuadEaseInOut(float t)
    {
        if (t < 0.5f)
            return 2.0f * Math::Pow(t, 2.0f);
        else
            return 1.0f - Math::Pow(-2.0f * t + 2.0f, 2.0f) / 2.0f;
    }

    float Interpolation::FloatCubicEaseIn(float t)
    {
        return Math::Pow(t, 3.0f);
    }

    float Interpolation::FloatCubicEaseOut(float t)
    {
        return 1.0f -  Math::Pow(1.0f - t, 3.0f);;
    }

    float Interpolation::FloatCubicEaseInOut(float t)
    {
        if (t < 0.5f)
            return 4.0f * Math::Pow(t, 3.0f);
        else
            return 1.0f - Math::Pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
    }

    float Interpolation::FloatExpEaseIn(float t)
    {
        if (t > 0.0f)
            return Math::Pow(2.0f, 10.0f * t - 10.0f);

        return 0.0f;
    }

    float Interpolation::FloatExpEaseOut(float t)
    {
        if (t > 1.0f)
            return 1.0f;

        return Math::Pow(2.0f, -10.0f * t);
    }

    float Interpolation::FloatExpEaseInOut(float t)
    {
        if (t < 0.0f)
            return 0.0f;
        else if (t > 1.0f)
            return 1.0f;
        else if (t < 0.5f)
            return Math::Pow(2.0, 20.0f * t - 10.0f) / 2.0f;

        return (2.0f - Math::Pow(2.0f, -20.0f * t + 10.0f)) / 2.0f;
    }

    float Interpolation::FloatBackEaseIn(float t)
    {
        constexpr float s = 1.70158f;
        return Math::Pow(t, 2.0f) * ((s + 1) * t - s);
    }

    float Interpolation::FloatBackEaseOut(float t)
    {
        constexpr float s = 1.70158f;
        t -= 1.0f;
        return (Math::Pow(t, 2.0f) * ((s + 1.0f) * t + s) + 1.0f);
    }

    float Interpolation::FloatBackEaseInOut(float t)
    {
        constexpr float s = 1.70158f * 1.525f;
        t *= 2.0f;
        if (t < 1.0f)
        {
            return 0.5f * (Math::Pow(t, 2.0f) * ((s + 1.0f) * t - s));
        }
        else
        {
            t -= 2.0f;
            return 0.5f * (Math::Pow(t, 2.0f) * ((s + 1.0f) * t + s) + 2.0f);
        }
    }

    float Interpolation::FloatElasticEaseIn(float t)
    {
        if (t == 0.0f || t == 1.0f)
            return t;

        constexpr float p = 0.3f;
        constexpr float a = 1.0f;
        constexpr float s = p / 4.0f;
        t -= 1.0f;
        return -(a * Math::Pow(2.0f, 10.0f * t) * Math::Sin((t - s) * (2.0f * M_PI) / p));
    }

    float Interpolation::FloatElasticEaseOut(float t)
    {
        if (t == 0.0f || t == 1.0f)
            return t;

        constexpr float p = 0.3f;
        constexpr float a = 1.0f;
        constexpr float s = p / 4.0f;

        return (a * Math::Pow(2.0f, -10.0f * t) * Math::Sin((t - s) * (2.0f * M_PI) / p) + 1.0f);
    }

    float Interpolation::FloatElasticEaseInOut(float t)
    {
        if (t == 0.0f || t == 1.0f)
            return t;

        constexpr float p = 0.3f * 1.5f;
        constexpr float a = 1.0f;
        constexpr float s = p / 4.0f;

        t *= 2.0f;

        if (t < 1.0f)
        {
            t -= 1.0f;
            return -0.5f * (a * Math::Pow(2.0f, 10.0f * t) * Math::Sin((t - s) * (2.0f * M_PI) / p));
        } else
        {
            t -= 1.0f;
            return a * Math::Pow(2.0f, -10.0f * t) * Math::Sin((t - s) * (2.0f * M_PI) / p) * 0.5f + 1.0f;
        }
    }
} // namespace ASEngine
