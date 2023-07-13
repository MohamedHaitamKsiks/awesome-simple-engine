
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
		//Scene::importAll();
		//load project settings
		application->loadProjectSettings();

		//init ecs world
		World::init();
	}

	Application* Application::getSingleton() {
		return application;
	}

	void Application::init() {
		// create default camera
		Camera::current = new Camera();
		//init renderer
		renderer.init();
		//init vbo
		VertexBufferObject::init();
		//init texture
		Texture::init();
		//init graphics
		graphics.init();
		//init unique string manager
		UniqueStringManager::init();

		//init resource managers
		ResourceManager<Sprite>::init();
		Sprite::importAll();
		
		ResourceManager<Font>::init();
		Font::importAll();

		Log::out("Application init complete");
	}


	void Application::onInputEvent(InputEvent &inputEvent) {
		// process event for each instance
	}

	void Application::update(float delta) {
		// update here..
		World::getSingleton()->update(delta);

		// init draw
		renderer.draw();

		// draw here ..
		World::getSingleton()->draw(graphics);

		// flush graphics
		graphics.update();
	}

	void Application::terminate() {
		// terminate graphics
		graphics.terminate();
		// destroy all vbo
		VertexBufferObject::terminate();
		//terminate textures
		Texture::terminate();
		// terminate resource managers
		ResourceManager<Sprite>::terminate();
		ResourceManager<Font>::terminate();
		ResourceManager<Scene>::terminate();
		//terminate world
		World::terminate();
		//delete camera
		delete Camera::current;
		//delete app
		delete application;
		application = nullptr;
		Log::out("application terminated!");
	}


	void Application::loadProjectSettings() {
		//load json file
		File projectSettingsFile;
		projectSettingsFile.open("project.settings.json", FILE_OPEN_MODE_READ);
		std::string projectSettingsString = projectSettingsFile.readText();
		projectSettingsFile.close();
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
		//Scene::changeSceneTo(projectMainScene);

	}

	Platform Application::getPlatform() {
		return platform;
	}

} // ASEngine