# Android Simple Engine

Android game engine written with native c++ and android studio.

## Features


### 2D OpenGL ES 2.0 Renderer

You can draw textures, sprites, colored rectangles and text.

The renderer uses batch rendering for performances with over 16 000 elements per in a single draw call.

You can draw in the screen using a Graphics object that is created with the Application.

Examples : 

````cpp
 
    graphics.drawSprite("spriteId", frame, position, scale, rotation, modulate);

    graphics.drawText("Hello World!", frame, fontId, position, modulate);
  
````

### Resource Manager

Most resources in the engine are referenced by a unique Id that can either be assigned by the user or generated.

The resources that we manage are:


#### 1. Images

Loading images from png files that can be used to generate textures to draw.

````cpp

    Image img = Image::load(imagePath);
    
    //we can use it to create textures in the gpu
    
    Texture texture = Texture::load(img);

````

img will have a automaticly generated ID

#### 2. Sprites

Adding sprites that we can draw using their Id.

````cpp

    Sprite::load("givenSpriteId", texture, frameNumber, offset);
    
    //we can access the sprite with the id for example to draw it
    
    graphics.drawSprite("givenSpriteId", frame, position, scale, rotation, modulate);

````

#### 3. Fonts

Fonts are pretty much like sprites

````cpp

    Font::load("givenFontId", size, fontPath, separation, lineSeparation, spaceSize);

````

#### 4. Scenes

Scenes are described in json files like these :

````json

{
  "instances": [
    {
      "name": "MyObject",
      "position": {
        "x": 120,
        "y": 120
      }
    },
    {
      "name": "MyObject",
      "position": {
        "x": 10,
        "y": 10
      }
    }
  ]
}

````

They are imported like sprites and fonts.

#### 5. Materials

They are not in point yet. 

While you can load materials. I don't think you should expect to use them yet since the my batch renderer is not compatible with using multiple materials.

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

3. Scenes

````json

[
  {
    "name": "sc_main",
    "file": "main.scene.json"
  }
]

````


### Game Objects and Instances

The engine uses a purely object oriented approach where all the Objects that are in Game inherites from the GameObject class.

It follows the same idea as GameMaker's Object but simpler.

The GameObject reacts to 4 main events:

- onCreate

- onUpdate

- onDraw

- onInputEvent

Example of creating a gameobject:

````cpp

#include "../../engine/asengine.h"

using namespace ASEngine;

class MyObject: public GameObject {

	void onCreate() {
        //on instance create
    }
    
	void onUpdate(float delta) {
        //on frame update
    }
    
	void onDraw(Graphics& graphics) {
        //what you want to draw on the screen
    }
    
	void onInputEvent(InputEvent event) {
        //on input event
    }

};

````

We are not done yet, to make your object usable you need to give him an Id.

You can do that in 'Objects/loadGameObject.h' file :

````cpp

//add every game object here
static void loadGameObjects() {
	ASEngine::Instance::addGameObject<MyObject>("MyObject");
}

````

Now that we have our gameobject we can create instances of it or add to a scene like the example above.

````cpp

MyObject* instance = Instance::create("MyObject");

````


