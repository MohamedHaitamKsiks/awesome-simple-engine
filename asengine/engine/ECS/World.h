#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H



namespace ASENGINE
{
    class World
    {
    public:
        // init singleton
        static void init();
        // get singleton
        static World* getSingleton();
        // terminate singleton
        static terminate();

        // add component type
        template <typename T>
        void addComponentType<T>();
        // remove component type
        template <typename T>
        void removeComponentType<T>();

        //  add system

        // add entity
        Entity addEntity();
        void removeEntity(Entity entity);
        // update the world
        void update(float delta);


    private:
        //singleton
        static World* world;
        

    };
    
} // namespace ASENGINE


#endif