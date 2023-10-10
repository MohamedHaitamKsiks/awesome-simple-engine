#ifndef ASENGINE_TIME_H
#define ASENGINE_TIME_H

namespace ASEngine
{
    class Time
    {
    public:
        // application time scale (controls speed of update)
        static float TimeScale;

        // fixed time step
        static float FixedTimeStep;
    };
    
}; // namespace ASEngine

#endif // ASENGINE_TIME_H