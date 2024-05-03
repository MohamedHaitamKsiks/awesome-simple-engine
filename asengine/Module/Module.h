#ifndef ASENGINE_MODULE_H
#define ASENGINE_MODULE_H

namespace ASEngine
{
    // module
    class IModule
    {
    public:
        virtual void Registry() = 0;
    };
    
} // namespace ASEngine

#endif // ASENGINE_MODULE_H