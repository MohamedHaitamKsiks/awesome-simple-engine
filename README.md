# Awesome Simple Engine

Cross-platform game engine written with c++.

## Features


### 2D OpenGL ES 2.0 Renderer

You can draw textures, sprites, colored rectangles and text.

The renderer uses batch rendering for performances with over 16 000 elements in a single draw call.

You can draw in the screen using a Graphics object that is created with the Application.

Examples : 

````cpp
 
    graphics.drawSprite(sprite, frame, position, scale, rotation, modulate);

    graphics.drawText("Hello World!", frame, fontId, position, modulate);
  
````

### Resource Manager

Most resources in the engine are referenced by a unique Id that can either be assigned by the user or generated.


The resources that we manage are:


#### 1. Images

Loading images from png files that can be used to generate textures to draw.

````cpp

    Image img;
    img.load(imagePath);
    
    //we can use it to create textures in the gpu
    
    Texture texture = Texture::load(img);

````


#### 2. Sprites

Adding sprites that we can draw.

````cpp

    Sprite sprite;
    sprite.load(texture, frameNumber, offset);
    
    //we can access the sprite with the id for example to draw it
    
    graphics.drawSprite(&sprite, frame, position, scale, rotation, modulate);

````

#### 3. Fonts

Fonts are pretty much like sprites

````cpp

    Font font;
    font.load(size, fontPath, separation, lineSeparation, spaceSize);

````

#### Using JSON file to load 

The resources can also be imported using json files in the assets folder.

Examples:

1. Sprites

````json

[
  {
    "name": "spr_run",
    "image": "spr_run.png",
    "frames": 6,
    "offset": {
      "x": 16.0,
      "y": 16.0
    }
  }
]

````

2. Fonts

````json

[
  {
    "name": "ft_pixel",
    "size": 24,
    "font": "nuku1.ttf",
    "separation": 4,
    "lineSeparation": 4,
    "spaceSize": 8
  }
]

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

#include "engine/asengine.h"

using namespace ASEngine;

struct SpriteComponent: Component<SpriteComponent> {

  ResourceID spriteId;
  float frame = 0.0f;
  float frameRate = 8.0f;

};

````

### System:

Create a class that inherits from System<Component1, Component2 ....>.

Example:
````cpp

#include "engine/asengine.h"

using namespace ASEngine;

// render sprites on screen
class SpriteRenderingSystem: public System<SpriteComponent, TransformComponent>
{
public:

    // on update
    void onUpdate(float delta)
    {
        forEach([&delta](SpriteComponent *sprite, TransformComponent *transform)
        {
            //behaviour...
        });
    }

    // on draw
    void onDraw(Graphics &graphics)
    {
        forEach([&graphics](SpriteComponent *sprite, TransformComponent *transform)
        {
            //behaviour...
        });
    }
};
````

### Entity:

You can create entities and delete them using the World singleton.

Example:
````cpp
  SpriteComponent sprite;
  TransformComponent tranform;

  // create entity
  Entity entity = World::getSingleton()->create(
      sprite,
      transform
  );

  // destroy entity
  World::getSingleton()->destroy(entity);
````



We are not done yet, you need to register your components and systems.

You can do that in 'ecs/registry.h' file :

````cpp

using namespace ASEngine;

// register ecs
void ECSRegistry()
{
    
    // component registry ...
    ComponentManager::getSingleton()->registerComponent<SpriteComponent>(UniqueString("Sprite"));
    ComponentManager::getSingleton()->registerComponent<TransformComponent>(UniqueString("Transform"));

    // system registry ...
    SystemManager::getSingleton()->registerSystem<SpriteRenderingSystem>();
};

````

### Particle System (Deprecated)

To you the particle system you have to create:

#### 1. ParticleDescriptor

They descript how the particles are behave (direction, velocity, angle ...).

````cpp

ParticleDescriptor descriptor{};

//velocity with random range 50 to 100
desriptor.velocity = {50.0f, 100.0f};

//direction always up
direction.direction = 0.5f * M_PI;


````

#### 2. ParticleEmitter

As you can understand from the name, it emits particles from a point or circle.

You can configure it with:

1. Particle descriptor

2. Sprite to draw

3. Explosiveness

4. Number of particles 

you can then emit with a single function call

````cpp

ParticleEmitter emitter{};

emitter.emit();

````

### Other Features

1. Interpolation

2. Math

3. Log

4. UniqueStrings


## Future of the engine.

The Engine is still under active development with many missing featues like: Input Management, Scene Management...