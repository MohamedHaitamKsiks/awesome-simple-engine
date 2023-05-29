//
// Created by ksiks_wa3r on 4/10/23.
//

#include "Application.h"

namespace ASEngine {


	bool Application::firstLoad = false;

	void Application::init(android_app* app) {
		//init resource manager
		Resource::init(app->activity->assetManager);
		//do this once
		if (!firstLoad) {
			//import scenes
			Scene::importAll();
			//load project settings
			loadProjectSettings();
			//set first load
			firstLoad = true;
		}
		//create context
		context = new Context(app);
		//init renderer
		renderer.init();
		//init vbo
		VertexBufferObject::init();
		//init texture
		Texture::init();
		//init graphics
		graphics.init();
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
		Instance::draw(graphics);
		//fps
		std::stringstream ss;
		ss << int(1.0f / delta) << " FPS\n";
		ss << Screen::getWindowWidth() << ", : . " << Screen::getWindowHeight();
		//draw fps
		for (int r = 1; r <= 2; r++) {
			if (r > 0) {
				graphics.drawText(ss.str(), vec2{16.0f + float(r-1), 16.0f + float(r-1)}, "ft_pixel", Color::black);
				graphics.drawText(ss.str(), vec2{16.0f - float(r-1), 16.0f - float(r-1)}, "ft_pixel", Color::black);
				graphics.drawText(ss.str(), vec2{16.0f + float(r-1), 16.0f - float(r-1)}, "ft_pixel", Color::black);
				graphics.drawText(ss.str(), vec2{16.0f - float(r-1), 16.0f + float(r-1)}, "ft_pixel", Color::black);
			}

			graphics.drawText(ss.str(), vec2{16.0f + float(r), 16.0f}, "ft_pixel", Color::black);
			graphics.drawText(ss.str(), vec2{16.0f - float(r), 16.0f}, "ft_pixel", Color::black);
			graphics.drawText(ss.str(), vec2{16.0f, 16.0f + float(r)}, "ft_pixel", Color::black);
			graphics.drawText(ss.str(), vec2{16.0f, 16.0f - float(r)}, "ft_pixel", Color::black);
		}


		graphics.drawText(ss.str(), vec2{16.0f, 16.0f}, "ft_pixel");
		//upadte graphics
		graphics.update();
		//flush context
		context->flush();
	}

	void Application::terminate() {
		//destroy all vbo
		VertexBufferObject::terminate();
		//terminate graphics
		graphics.terminate();
		//terminate textures
		Texture::terminate();
		//terminate resources
		Resource::terminate();
		Material::terminate();
		Sprite::terminate();
		Font::terminate();
		Image::terminate();
		//destroy context
		delete context;
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

	void Application::loadProjectSettings() {
		//load json file
		std::string projectSettingsString = Resource::loadAsText("project.settings.json");
		//parse to json
		nlohmann::json projectSettings = nlohmann::json::parse(projectSettingsString);
		//get settings
		std::string projectName = projectSettings["name"];
		//set window size
		int projectWindowWidth = projectSettings["windowSize"]["width"];
		int projectWindowHeight = projectSettings["windowSize"]["height"];
		Screen::setSize(projectWindowWidth, projectWindowHeight);
		//set main scene
		std::string projectMainScene = projectSettings["mainScene"];
		Scene::changeSceneTo(projectMainScene);

	}

} // ASEngine