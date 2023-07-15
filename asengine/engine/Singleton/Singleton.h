#ifndef ASENGINE_SINGLETON_H
#define ASENGINE_SINGLETON_H

#include "engine/Log/Log.h"

namespace ASEngine
{

    /*
        definition for singleton template
        just to avoid rewrite alot of code that is basically the same for
        all singletons in the engine
    */
    template<typename T>
    class Singleton
    {
        public:
            // init singleton
            static void init();
            // get singleton
            static T* getSingleton();
            // terminate singleton
            static void terminate(); 

        private:
            static T* singleton;
    };

} // namespace ASEngine

#include "Singleton.cpp"


#endif