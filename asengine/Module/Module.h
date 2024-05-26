#ifndef __ASENGINE_MODULE_H
#define __ASENGINE_MODULE_H

namespace ASEngine
{
    // module
    class IModule
    {
    public:
        virtual void Registry() = 0;
    };
    
} // namespace ASEngine

#endif // __ASENGINE_MODULE_H