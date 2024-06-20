#ifndef __ASENGINE_DESKTOP_APPLICATION_H
#define __ASENGINE_DESKTOP_APPLICATION_H


#include <sstream>
#include <iostream>
#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "ASEngine.h"

namespace ASEngine
{
    
    class DesktopApplication 
    {
    public:
        int Run();
        ~DesktopApplication();

    private:

        // asengine application
        ASEngine m_ASEngine{};

        // create window for desktop application
        bool Init();

        //update desktop application
        void Update(float delta);

        //derminate desktop application
        void Terminate();
    };

} // namespace ASEngine

#endif