#ifndef __ASENGINE_API_H
#define __ASENGINE_API_H

#ifdef _WIN32
    #ifdef ASENINE_EXPORTS
        #define ASENGINE_API __declspec(dllexport)
    #else
        #define ASENGINE_API __declspec(dllimport)
    #endif
#else
    #define ASENGINE_API
#endif

#endif // __ASENGINE_API_H