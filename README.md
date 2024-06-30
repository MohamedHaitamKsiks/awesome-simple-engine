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

### API Agnostic Renderer

ASEgnine offers a low level renderer that gives the user more control while also being easier to use than your typical OpenGL or Vulkan. 

Only OpenGL is supported for now. But I plan to add Vulkan soon.

### Buffers

Buffers are used to store data in the GPU. There are 3 types of buffers:

1. Array Buffers 
2. Index Buffers
3. Uniform Buffers

Example:

```cpp
// create your buffer
ResourceRef<Buffer> myBuffer = Buffer::GetResourceClass().New();
myBuffer->Create(BufferType::ARRAY);

// send data
myBuffer->SetData(data, size);
```

### Textures

A texture is an image stored in the GPU which can be used for rendering.

Example:
```cpp
// load the png 
Image image{};
image.LoadPNG("path.to.image.png");

// create the texture
ResourceRef<Texture> myTexture = Texture::GetResourceClass().New();

myTexture->Create(image, TextureFilter::LINEAR, TextureRepeatMode::REPEAT);
```

Textures are serializable resources so you can create them in your assets folder as json files:

```json
{
  "ImagePath": "textures/leaf.png",
  "Filter": "NEAREST",
  "RepeatMode": "REPEAT"
}
```

You can then load them like this:

```cpp
ResourceRef<Texture> texture = Texture::GetResourceClass().Load("textures/lead.texture.json");
```

### Shaders

ASEngine supports Vulkan GLSL. When you build your game project all the shaders present in the assets folder gets compiled to their .spirv equivilent. 

Make sure your shader codes ends with .frag .vert.

To create a shader your need to provide it wiht the vertex ShaderSource and the fragment ShaderSource.
In addition you will need a VertexInputDescriptor to give it the layout of the vertex data.

Example:

1. Vertex shader:

```glsl
#version 450

//attribute
layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec4 v_Modulate;

// outs
layout(location = 0) out vec4 MODULATE;

// main function is generated
void main() {
    MODULATE = v_Modulate;
    gl_Position = vec4(vec3(v_Position, 0.0), 1.0);
}

```

2. Fragment shader:

```glsl
#version 450

layout(location = 0) in vec4 MODULATE;
layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = MODULATE;
}

```

3. VertexInputDescriptor

```json
{  
  "VertexInputLayouts":
  [
    {
      "Binding": 0,
      "InputRate": "VERTEX",
      "VertexAttributes":
      [
        {
            "Location": 0,
            "Type": "VEC2"
        },
        {
            "Location": 1,
            "Type": "VEC4"
        }
      ]
    }
  ]
}
```

Creating the shader:

```cpp
// importing sources and descriptor
ResourceRef<ShaderSource> vertexSource = ShaderSource::GetResourceClass().Load("shaders/test.vert");
ResourceRef<ShaderSource> fragmentSource = ShaderSource::GetResourceClass().Load("shaders/test.frag");
ResourceRef<VertexInputDescriptor> descriptor = VertexInputDescriptor::GetResourceClass().Load("shaders/test.descriptor.json");

// create shader
ResourceRef<Shader> shader = Shader::GetResourceClass().New();
shader->Create(vertexSource, fragmentSource, descriptor);
```

You can also create the shader in your assets folder as a json file:

```json
{
  "Vertex": "shaders/test.vert",
  "Fragment": "shaders/test.frag",
  "VertexInputDescriptor": "shaders/test.descriptor.json"
}
```

### Materials

A material is linked to a shader. It contains all the uniform data for the material.

Example:

```cpp
ResourceRef<Material> material = Material::GetResourceClass().New();

material->Create(shader);

material->SetShaderParam("Wold", "Position", worldPosition);
material->SetShaderParam("Texture", myTexture);
```

Materials are serializable resources. You can create them as json files in the assets folder.

```json
{
    "Shader": "shaders/default2D/default2D.shader.json",
    "UniformBuffers":
    {
      "World":
      {
        "Position":
        {
          "x": 5.0,
          "y": 2.0,
          "z": 0.0
        }
      }
    },
    "Samplers":
    {
        "Texture": "textures/leaf.texture.json"
    }
}
```

### Renderer System

To make a draw call your need to

1. Bind the vertex buffers

```cpp
Renderer::GetInstance().BindVertexBuffer(vertexBuffer, binding);
```

2. Bind the index buffer

```cpp
Renderer::GetInstance().BindIndexBuffer(indexBuffer);
```

3. Bind a material
```cpp
Renderer::GetInstance().BindMaterial(material);
```

You can also bind a shader and set the uniform buffers manually.

4. Make a draw class

```cpp
Renderer::GetInstance().DrawElements(indexCount);
```

or if you want to use GPU Instancing

```cpp
Renderer::GetInstance().DrawElements(indexCount, instanceCount);
```

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
ASENGINE_REGISTER_RESOURCE_CLASS(Buffer);
```

If you want a resource class with different implementations (useful for API agnostic architectures), you can register your resource class like this:
```cpp
ASENGINE_REGISTER_ABSTRACT_RESOURCE(Buffer, OpenGLBuffer); 
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
    ASENGINE_REGISTER_COMPONENT(SpriteComponent);

    // system registry ...
    ASENGINE_REGISTER_SYSTEM(SpriteRenderingSystem);
````


### Other Features

1. Math

2. Log

3. UniqueStrings


## Future of the engine.

The Engine is still under active development with many missing featues.