//
// Created by ksiks_wa3r on 4/10/23.
//

#include "Application.h"

namespace ASEngine {

	void Application::init(android_app* app) {
		//create context
		context = new Context(app);
		//init renderer
		renderer.init();
		//init resource manager
		Resource::init(app->activity->assetManager);
		//init vbo
		VertexBufferObject::init();
		//init texture
		Texture::init();
		//init graphics
		Graphics::init();
		//load sprites
		Sprite::importAll();
		//load materials
		Material::importAll();
		//load fonts
		Font::importAll();
		//create default camera
		Camera::current = new Camera();
		//init input
		InputEvent::init(app);
	}

	void Application::onInputEvent(InputEvent &inputEvent) {
		//process event for each instance
		for (auto instance: Instance::instances) {
			instance->onInputEvent(inputEvent);
		}
	}

	void Application::update(float delta) {
		//update instance
		Instance::update(delta);
		//context update render area
		context->updateRenderArea();
		//draw
		renderer.draw();

		//draw instances
		Instance::draw();
		//fps
		std::stringstream ss;
		ss << int(1.0f / delta) << " FPS";
		//draw fps
		Graphics::drawText(ss.str(), vec2{16.0f, 18.0f}, "ft_pixel", Color::black);
		Graphics::drawText(ss.str(), vec2{16.0f, 17.0f}, "ft_pixel");
		//upadte graphics
		Graphics::update();
		//flush context
		context->flush();
	}

	void Application::terminate() {
		//destroy context
		delete context;
		//destroy all vbo
		VertexBufferObject::terminate();
		//terminate textures
		Texture::terminate();
		//terminate resources
		Resource::terminate();
		Material::terminate();
		Sprite::terminate();
		Font::terminate();
		//delete camera
		delete Camera::current;
	}

	void Application::poolAndroidInput(android_app* app) {
		//pool every input on queue
		for(size_t i = 0; i < app->motionEventsCount; ++i) {
			//pool event
			InputEvent event = InputEvent::poolEvent(i);
			//process input
			onInputEvent(event);
		}
	}

} // ASEngine