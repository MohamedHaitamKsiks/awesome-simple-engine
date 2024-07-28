# Awesome Simple Engine

Cross-platform game engine written with c++.

## Dependencies

### Debian / Ubuntu

Install depencies:

```sh
#install emsdk for web
./install_emsdk.sh

#other dependencies
sudo apt update &&
sudo apt-get -y install cmake &&
sudo apt-get -y install g++-mingw-w64 &&
sudo apt-get -y install freeglut3-dev &&
sudo apt-get -y install xorg-dev libgl1-mesa-dev
```

## Setup

To compile and run unit test of the engine run the setup.py script

```sh
python3 setup.py
```

## Run Demos

Demos are located in the /demos folder. You can run them with this command:

```sh
./run_demo.sh <demo-name> <platform-name>
```

Example:

Running Example2D demo:

```sh
./run_demo.sh Example2D linux
```

![10,0000 sprites](./screenshots/10000_sprites_example.png?raw=true)


## Features

### 2D Module

ASEngine offers a high level 2D Module that supports Transform Hiearchy, Sprites, Text rendering, and other drawing functions.
The 2D renderer uses batching to reduce the number of draw calls. 

You can add it to your project in the registry function: 

```sh
Module2D::Init();
```

You can check out the Example2D demo in the demos folder to test this module.

### Renderer2D


Renderer2D is a singleton system responsible for rendering 2D graphics. It offers a range of functionalities:

#### Renderer Settings:
They are loaded from the renderer2d.settings.json files located in the assets folder.

Example:

```json
{
  "Layers": ["Default", "PixelViewport"],
  "DefaultMaterial": "materials/default2D.material.json"
}
```

#### Layer Management:

1. GetLayer(UniqueString layerName): Retrieve a specific layer by name.
2. GetLayerNames(): Retrieve all layer names.


#### Resource Accessors:

1. GetDefaultShader(): Access the default shader.
2. GetDefaultMaterial(): Access the default material.
3. GetFillRectangleDefaultMaterial(): Access the default material for filling rectangles.
4. GetFillRectangleTexture(): Access the texture used for filling rectangles (one white pixel).

#### Render Signal:

Rendering operations should be performed within the RenderSignal event to ensure that all custom rendering logic is executed correctly and efficiently. This approach allows you to hook into the rendering pipeline and execute rendering commands in a structured and organized manner.

You can get the render signal with the GetOnRendere2D() method:

```cpp
// add on render
m_OnRender2DConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this](Renderer2D& renderer2D)
{
  OnRender2D(renderer2D);
});
```

### Layer2D

The Layer2D class provides a suite of methods for rendering 2D graphics onto a specific layer. This class supports various drawing operations including shapes, sprites, and text, with customization options for materials and alignment.

Some drawing operations:

#### 1. Draw quads
```cpp
// Example of drawing a quad and retrieving the Quad2D object
Layer2D& layer = renderer2D.GetLayer("Default");
ResourceRef<Material> material = /* load your material */;
Quad2D& quad = layer.DrawQuad2D(material);
// Modify the quad
quad2D.Create(size, transform, color, Vector2::ZERO(), Vector2::ONE());
```

#### 2. Draw sprites

```cpp
// Example of drawing a sprite
Layer2D& layer = renderer2D.GetLayer("Default");
ResourceRef<Sprite> sprite = Sprite::GetResourceClass().Load("sprites/your.sprite.json");
Matrix3x3 transform = Matrix3x3::Translate(Vector2(32.0f, 32.0f));
uint32_t hframe = 0; // Horizontal frame index
uint32_t vframe = 0; // Vertical frame index
layer.DrawSprite(sprite, transform, hframe, vframe, Color::WHITE());
```

#### 3. Draw rectangles

```cpp
// Example of drawing a filled rectangle
Layer2D& layer = renderer2D.GetLayer("Default");
Vector2 size(100.0f, 50.0f); // Width and height of the rectangle
Matrix3x3 transform = Matrix3x3::IDENTITY();
layer.DrawFillRectangle(size, transform, Color::RED());
```

#### 4. Draw lines
```cpp
// Example of drawing a line
Layer2D& layer = renderer2D.GetLayer("Default");
Vector2 start(0.0f, 0.0f); // Start point of the line
Vector2 end(100.0f, 100.0f); // End point of the line
float lineThickness = 2.0f; // Thickness of the line
Matrix3x3 transform = Matrix3x3::IDENTITY();
layer.DrawLine(start, end, lineThickness, transform, Color::RED());
```

#### 5. Draw text
```cpp
// Example of drawing text
Layer2D& layer = renderer2D.GetLayer("Default");
ResourceRef<Font> font = Font::GetResourceClass().Load("fonts/your.font.json");
Matrix3x3 transform = Matrix3x3::IDENTITY();
layer.DrawText(font, "Hello World", transform, Color::WHITE());
```

#### 6. Draw text with alignement
```cpp
// Example of drawing text with alignment
Layer2D& layer = renderer2D.GetLayer("Default");
ResourceRef<Font> font = Font::GetResourceClass().Load("fonts/your.font.json");
Matrix3x3 transform = Matrix3x3::IDENTITY();
layer.DrawTextAlign(font, "Hello World!", transform, TextHorizontalAlign::CENTER, TextVerticalAlign::MIDDLE, Color::WHITE());
```

### Sprites

A Sprite is a resource that consists of multiple frames arranged in a grid within a single Texture. 

Example:

```json
{
  "Texture": {
    "ImagePath": "textures/spr_run.png",
    "Filter": "NEAREST",
    "RepeatMode": "REPEAT"
  },

  "HFrames": 6,
  "VFrames": 1,

  "RelativeToCenter": true,
  "Offset": {
    "x": 0.0,
    "y": 0.0
  }
}
```

### Fonts

Fonts in ASEngine are also resources treated in a manner similar to sprites. When a font is created, it generates a spritesheet grouping all character in the font. This process allows the text to be rendered efficiently during runtime.

Example of font:
```json
{
  "FontPath": "fonts/kongtext.ttf",
  "Size": 32,
  "CharacterSeparation": 4,
  "LineSeparation": 4,
  "SpaceSize": 32
}
```

### Transform2D

Transform2D is a component designed for handling 2D transformations of entities. 

It provides properties for managing position, scale, and rotation, and methods to compute local and global transformation matrices. 

The component also supports parent-child relationships, allowing for hierarchical transformations. 

Key methods:
 1. GetLocalTransform(): returns the local transformation matrix.
 2. GetGlobalTransform(): returns the global transformation matrix incorporating parent transformations. 

For efficient performance, it's recommended to cache global transformation results when possible.

Example:

```json
"Transform2D": {
  "Position": {
    "x": 0.0,
    "y": 0.0
  },
  "Scale": {
    "x": 1.0,
    "y": 1.0
  },
  "Rotation": 0.0,
  "Entities": [
    /* your child entities here ... */
  ]
}
```

### Camera2D

Camera2D is a component used for managing 2D camera properties. 

It includes a Target property to specify the viewport, a PixelSnapping option to enable or disable snapping of the camera position to pixel boundaries, and a set of Layers to control which layers the camera will render. 

The Transform2D component is required for the camera to render entities into the target. 

If the Target is set to NONE, the camera renders directly to the screen. 

Example:

```json
{
  "Camera2D": {
    "Layers": ["Default"],
    "PixelSnapping": true,
    "Target": "viewports/pixel.viewport.json"
  },
  "Transform2D": {
    "Position": {
      "x": 0.0,
      "y": 0.0
    },
    "Scale": {
      "x": 1.0,
      "y": 1.0
    },
    "Rotation": 0.0,
    "Entities": []
  }
}
```


### Low Level Renderer

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

A texture is an image stored in the GPU.

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

Make sure your shader codes ends with .frag or .vert.

To create a shader your need to provide it with the vertex and fragment ShaderSources.
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

A material is linked to a shader. It contains all the uniform data and samplers for the material.

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

### Viewports

Viewports are rendering contexts that allow you to draw onto a framebuffer and retrieve the results as textures.

Example:

```cpp
ResourceRef<Viewport> viewport = Viewport::GetResourceClass().New();
viewport->Create(320, 180, 1);
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

All rendering commands needs to be done in a viewport context.

```cpp

Renderer::GetInstance().Begin(viewport);

// Draw commands to viewport

Renderer::GetInstance().End();

// ...

Renderer::GetInstance().Begin();

// Draw commands to backbuffer

Renderer::GetInstance().End();

```

### Resource Manager

Resources are garbage collected objects that can be loaded from a file or created programmatically.

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
struct SpriteRenderer: public Component<SpriteComponent>
{
  ResourceRef<Sprite> SpriteToRender;
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
    EntityQuery<SpriteRenderer, TransformComponent>query{};

    // if you have a small number of components you can use this
    query.ForEach([&delta](SpriteComponent& sprite, TransformComponent& transform)
    {
      //behaviour...
    });

    // for better performances use this
    query.ForEachCollection([&delta](ComponentCollection<SpriteRenderer>& sprites, ComponentCollection<TransformComponent>& transforms, size_t count)
    {
      for (size_t i = 0; i < count; i++)
      {
        // behaviour
      }
    });
  }
};
````

### Entity:

You can create entities and delete with the help of an entity builder.

Example:
````cpp
  SpriteRenderer sprite{};
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
    ASENGINE_REGISTER_COMPONENT(SpriteRenderer);

    // system registry ...
    ASENGINE_REGISTER_SYSTEM(SpriteRenderingSystem);
````


### Other Features

1. Math

2. Log

3. UniqueStrings


## Future of the engine.

The Engine is still under active development with missing important features.
