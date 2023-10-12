#ifndef ASENGINE_MODULE_H
#define ASENGINE_MODULE_H

namespace ASEngine
{
    // module interface
    class IModule
    {
    public:
        // register components
        virtual void RegisterComponents() {};

        // register systems
        virtual void RegisterSystems() {};

        // init resources managers
        virtual void InitResourceManagers() {};

        // terminate resource managers
        virtual void TerminateResourceManagers(){};
    };
    
} // namespace ASEngine

#endif // ASENGINE_MODULE_H