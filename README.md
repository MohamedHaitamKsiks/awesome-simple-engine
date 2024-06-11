# Awesome Simple Engine

Cross-platform game engine written with c++. 

## Dependencies
  
  ### Debian / Ubuntu

  Install depencies:

  ```sh
    $ sudo apt update &&
    $ sudo apt-get -y install cmake &&
    $ sudo apt-get -y install g++-mingw-w64 && 
    $ sudo apt-get -y install freeglut3-dev
  ```

  ### Windows

  Use WSL to run ubuntu commands and install dependencies.

## Features

### 3D Renderer

The renderer uses a mix of batching and gpu instancing to optimise draw calls. 

Let's draw some cubes as a example:
```cpp
  // ...
  // register mesh
  Mesh3D mesh = Renderer3D::RegisterMesh(cubeMeshInfo);
  //...

  // init mesh instance info
  MeshInstanceInfo3D meshInstaneInfo;
  meshInstaneInfo.Mesh = mesh;
  meshInstaneInfo.MaterialID = ResourceManager<Material>::GetResourceId(UniqueString("materials/material3D.json"));
  // init list of transforms each one is going to result in a new instance of the mesh.
  meshInstaneInfo.Transforms = TDynamicArray<mat4>();

  // add transforms ...

  // register mesh isntance 
  MeshInstance3D instance = Renderer3D::RegisterMeshInstance(meshInstanceInfo);


```


### 2D Renderer

The renderer uses batch rendering with 16000 quads per draw call.

Example:
````cpp
  Quad2D quad = Quad2D(size, transform, color);
  Renderer2D::DrawQuad(quad, materialID);
````

### Resource Manager

Resource are garbage collected objects that can be loaded from a file o created by the programmer.

Resources are always accessed using a ResourceReference.

```cpp
// getting resource class
auto& textureClass = Texture::GetResourceClass();

// creating reference
ResourceRef<Texture> createdTexture = textureClass.New();

// loading resource
ResourceRef<Texture> loadedTexture = textureClass.Load("assets/example.texture.json");

// automatically destroyed if not needed 
```

### Create a resource class

Example of resource resource class:

Header file:
```cpp
class Buffer: public Resource
{
ASENGINE_DEFINE_RESOURCE(Buffer);
public:
  virtual ~Buffer() {};

  // create buffer
  void Create(BufferType type);

private:
  BufferType m_Type = BufferType::NONE;
};
```

Source file:
```cpp
ASENGINE_SERIALIZE_RESOURCE_REF(Buffer);

// ...
```

Your register your resource class like this:
```cpp
ResourceManager::GetInstance().RegisterResourceClass<Buffer>("Buffer");
```

If you want a resource class with different implementations (useful for API agnostic architectures), you can register your resource class like this:
```cpp
ResourceManager::GetInstance().RegisterAbstractResourceClass<Buffer, OpenGLBuffer>("Buffer"); 
```

### Entity Component System

The engine uses a pure ECS architecture. With:

1. Entity: just an ID

2. Component: Data only with no behaviour

3. System: Behaviour of entities that has some given components

### Component:

Create a struct that inherits from Component.

Example:

````cpp
struct SpriteComponent: public Component<SpriteComponent> 
{
  ResourceID SpriteID;
  float Frame = 0.0f;
  float FrameRate = 8.0f;

  void OnCreate() override;
  void OnDestroy() override;
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
  // update
  void Update(float delta)
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
  auto& entityManager = EntityManager::GetInstance();
  EntityID entityID = entityManager.Create(builder);

  // destroy entity
  entityManager.Destroy(entityID);
````

We are not done yet, you need to register your components and systems to the module your working on.

````cpp
    // component registry ...
    ComponentManager::GetInsatance().RegisterComponent<SpriteComponent>("Sprite");

    // system registry ...
    SystemManager::GetInsatance().RegisterSystem<SpriteRenderingSystem>();
};

````


### Other Features

1. Math

2. Log

3. UniqueStrings


## Future of the engine.

The Engine is still under active development with many missing featues.