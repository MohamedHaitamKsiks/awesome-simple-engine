//
// Created by ksiks_wa3r on 4/10/23.
//

#include "Application.h"

namespace ASEngine {
	//application singletong
	Application* Application::application = nullptr;

	Application::Application(Platform _platform) {
		platform = _platform;
		if (application){
			delete this;
		}
	}

	void Application::create(Platform _platform) {
		if (application)
			return;
		application = new Application(_platform);
		//import scenes
		Scene::importAll();
		//load project settings
		application->loadProjectSettings();
	}

	Application* Application::getSingleton() {
		return application;
	}

	void Application::init() {
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
	}

	/*
	void Application::onInputEvent(InputEvent &inputEvent) {
		//process event for each instance
		for (auto instance: Instance::instances) {
			instance->onInputEvent(inputEvent);
		}
	}
	*/

	void Application::update(float delta) {
		//update instance
		Instance::update(delta);
		//draw
		renderer.draw();
		//draw instances
		Instance::draw(graphics);
		//upadte graphics
		graphics.update();
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
		//delete camera
		delete Camera::current;
	}

	/*
	void Application::poolAndroidInput(android_app* app) {
		//pool every input on queue
		for(size_t i = 0; i < app->motionEventsCount; ++i) {
			//pool event
			InputEvent event = InputEvent::poolEvent(i);
			//process input
			onInputEvent(event);
		}
	}
	 */

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