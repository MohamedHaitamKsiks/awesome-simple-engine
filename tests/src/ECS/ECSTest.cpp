#include "ECSTest.h"

#include <vector>
#include <memory>
#include <future>

// define OOP alternative to test performance
class GameObject
{
public:
    virtual void Update()
    {
        m_Position = Vector2{Random::Float(), Random::Float()};
    }

protected:
    Vector2 m_Position = Vector2::ZERO();
    float m_Angle;
};

class PhysicsBody: public GameObject
{
public:
    void Update() override
    {
        GameObject::Update();
        m_Position += m_Velocity;
    }

private:
    Vector2 m_Velocity = Vector2::ZERO();
};

class PlayerBody : public PhysicsBody
{
public:
    PlayerBody() {};

    void Update() override
    {
        PhysicsBody::Update();
        m_Counter++;
    }

    int m_Counter = 0;
};


// define components
struct Transform: public Component<Transform>
{
public:
    Vector2 Position = Vector2::ZERO();
    float Angle = 0.0f;

private:
    void OnCreate(EntityID entityID) override
    {
    }

    void OnDestroy() override
    {

    }
};

ASENGINE_EXPORT(Transform, Position, Angle);

struct Body: public Component<Body>
{
public:
    Vector2 Velocity = Vector2::ZERO();

private:
    void OnCreate(EntityID entityID) override
    {
    }

    void OnDestroy() override
    {
    }
};

ASENGINE_EXPORT_EMPTY(Body);

struct Player: public Component<Player>
{
public:
    int Counter = 0;

private:
    void OnCreate(EntityID entityID) override
    {
    }

    void OnDestroy() override
    {
    }
};

ASENGINE_EXPORT_EMPTY(Player);

// physcis system
class PhysicsSystem
{
public:

    void Update()
    {
        EntityQuery<Transform> query2{};
        query2.ForEachCollection([](ComponentCollection<Transform>& transforms, size_t count)
        {
            for (size_t i = 0; i < count; i++)
            {
                transforms[i].Position = Vector2{Random::Float(), Random::Float()};
            }
        });
        
        EntityQuery<Transform, Body> query{};
        query.ForEachCollection([](ComponentCollection<Transform>& transforms, ComponentCollection<Body>& bodies, size_t count)
        {
            for (size_t i = 0; i < count; i++)
            {
                transforms[i].Position += bodies[i].Velocity;
            }
        });

    
        EntityQuery<Player> query3{};
        query3.ForEachCollection([](ComponentCollection<Player>& players, size_t count)
        {
            for (size_t i = 0; i < count; i++)
            {
                players[i].Counter++;
            }
        });

    }

};
// test body
void ECSTest::Describe()
{
    Test("It can register component", []()
    {
        ASENGINE_REGISTER_COMPONENT(Transform);
        ASENGINE_REGISTER_COMPONENT(Body);
        ASENGINE_REGISTER_COMPONENT(Player);

        ASENGINE_EXPECT(Transform::GetName() == UniqueString("Transform"));
    });

    
    Test("It can create entities", []()
    {
        EntityBuilder builder;

        Transform transform{};
        transform.Position = Vector2{50.0f, 50.0f};
        transform.Angle = Math::PI / 4.0f;

        Body body{};
        body.Velocity = Vector2::ZERO();

        builder.AddComponents(transform, body);

        EntityID entityID = EntityManager::GetInstance().Create(builder);
        
        EntityManager::GetInstance().Destroy(entityID);
        EntityManager::GetInstance().CleanDestroyQueue();
    });


    Test("It can query over entities with Transform and Body components", []()
    {

        Transform transform{};
        transform.Position = Vector2{50.0f, 50.0f};
        transform.Angle = Math::PI / 4.0f;

        Body body{};
        body.Velocity = Vector2::ZERO();

        EntityBuilder builder;
        builder.AddComponents(transform, body);

        constexpr int transformBodyCount = 5;
        constexpr int transformCount = 3;

        // create entity with transform and body components
        for (int i = 0; i < transformBodyCount; i++)
            EntityManager::GetInstance().Create(builder);

        // create entities with transfome
        EntityBuilder builderTrasnformOnly;
        builderTrasnformOnly.AddComponents(transform);
        for (int i = 0; i < transformCount; i++)
            EntityManager::GetInstance().Create(builderTrasnformOnly);

        // transform body 
        int entityCount = 0;
        EntityQuery<Transform, Body> query{};
        query.ForEach([&entityCount](Transform& transform, Body& body)
        {
            ASENGINE_EXPECT(Math::Abs(transform.Angle - Math::PI / 4.0f) < 0.001f);
            entityCount ++;
        });
        ASENGINE_EXPECT(entityCount == transformBodyCount);

        // transform
        entityCount = 0;
        EntityQuery<Transform> queryTransform{};
        queryTransform.ForEach([&entityCount](Transform& transform)
        {
            entityCount ++;
        });
        ASENGINE_EXPECT(entityCount == transformBodyCount + transformCount);

        EntityManager::GetInstance().DestroyAll();
        EntityManager::GetInstance().CleanDestroyQueue();
    });
    

    Test("It is faster than OOP", []()
    {
        constexpr int entityCount = 500000;
        
        // create game objects
        std::vector<std::unique_ptr<GameObject>>gameObjects = {};
        for (int i = 0; i < entityCount; i++)
        {
            if (i % 2 == 0)
            {
                std::unique_ptr<GameObject> object = std::make_unique<PlayerBody>();
                gameObjects.push_back(std::move(object));
            }
            else
            {
                std::unique_ptr<GameObject> object = std::make_unique<GameObject>();
                gameObjects.push_back(std::move(object));
            }
        }

        // get delta time of oop appreadch
        auto pastTime = std::chrono::high_resolution_clock::now();

        for (auto& object: gameObjects)
            object->Update();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float oopDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count();
        Debug::Log("OOP Delta Time", oopDeltaTime / 1000.0f, "ms");

        // create entities
        Transform transform{};
        transform.Position = Vector2{50.0f, 50.0f};
        transform.Angle = Math::PI / 4.0f;

        Body body{};
        body.Velocity = Vector2::ZERO();

        Player player{};

        // [Transform, Body]
        EntityBuilder builder;
        builder.AddComponents(transform, body, player);

        for (int i = 0; i < entityCount / 2; i++)
            EntityManager::GetInstance().Create(builder);

        EntityBuilder builder2;
        builder2.AddComponents(transform);

        // [Transform]
        for (int i = 0; i < entityCount / 2; i++)
            EntityManager::GetInstance().Create(builder2);

        PhysicsSystem s{};

        //get delta time of ecs
        pastTime = std::chrono::high_resolution_clock::now();

        s.Update();

        currentTime = std::chrono::high_resolution_clock::now();
        float ecsDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count();
        Debug::Log("ECS Delta Time", ecsDeltaTime / 1000.0f, "ms");

        ASENGINE_EXPECT(ecsDeltaTime < oopDeltaTime);

        // clean up when I optimize the destroy all function
        // EntityManager::GetInstance().DestroyAll();

    });
}