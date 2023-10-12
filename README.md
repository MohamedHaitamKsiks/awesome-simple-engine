# Awesome Simple Engine

Cross-platform game engine written with c++.

## Features


### 2D OpenGL Renderer

The renderer uses batch rendering with 16000 quads per draw call.

Example:
````cpp
  Quad2D quad = Quad2D(size, transform, color);
  Renderer2D::DrawQuad(quad, materialID);
````

### Resource Manager

Most resources in the engine are referenced by a unique Id that can either be assigned by the user or generated.


The default resources are:


#### 1. Images

Loading images from png files that can be used to generate textures to draw.

````cpp
    Image img;
    img.load(imagePath);
    
    //we can use it to create textures in the gpu
    Texture texture = Texture::LoadFromImage(img);
````

#### 2. Shaders

````cpp
    Shader shader;
    shader.Load("shaders/default.glsl");
````

#### 3. Materials

Create material depending of shader.

````cpp
  Material mat;
  mat.Create(shaderId);
  mat.SetShaderParam(UniqueString("u_Texture"), texture);
````

### Entity Component System

The engine uses a pure ECS architecture. With:

1. Entity: just an ID

2. Component: Data only with no behaviour

3. System: Behaviour of entities that has some given components

### Component:

Create a struct that inherits from Component.

Example:

````cpp
struct SpriteComponent: Component<SpriteComponent> {
  ResourceID SpriteID;
  float Frame = 0.0f;
  float FrameRate = 8.0f;
};
````

### System:

Create a class that implements ISystem.

Example:
````cpp
// render sprites on screen
class SpriteRenderingSystem: public ISystem
{
public:

    // on update
    void OnUpdate(float delta)
    {
        // query components
        TEntityQuery<SpriteComponent, TransformComponent>query{};
        
        query.ForEach([&delta](SpriteComponent& sprite, TransformComponent& transform)
        {
            //behaviour...
        });
    }
};
````

### Entity:

You can create entities and delete with the help of an entity builder.

Example:
````cpp
  SpriteComponent sprite{};
  TransformComponent tranform{};

  EntityBuilder builder;
  builder.AddComponents(sprite, transform);

  // create entity
  Entity entity = World::Create(builder);

  // destroy entity
  World::Destroy(entity);
````

We are not done yet, you need to register your components and systems to the module your working on.

````cpp
    // component registry ...
    ComponentManager::RegisterComponent<SpriteComponent>(UniqueString("Sprite"));

    // system registry ...
    SystemManager::RegisterSystem<SpriteRenderingSystem>();
};

````


### Other Features

1. Interpolation

2. Math

3. Log

4. UniqueStrings

5. Modules


## Future of the engine.

The Engine is still under active development with many missing featues.