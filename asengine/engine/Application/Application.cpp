
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
		//init unique string manager
		UniqueStringManager::init();

		//init resource managers
		ResourceManager<Sprite>::init();
		Sprite::importAll();
		
		ResourceManager<Font>::init();
		Font::importAll();
		// manually import some resources to try the new system
		//create default camera
		Camera::current = new Camera();

		Log::out("Application init complete");
	}


	void Application::onInputEvent(InputEvent &inputEvent) {
		// process event for each instance
	}

	void Application::update(float delta) {
		// update here..

		// init draw
		renderer.draw();

		// draw here ..
		
		// flush graphics
		graphics.update();
	}

	void Application::terminate() {
		//destroy all vbo
		VertexBufferObject::terminate();
		//terminate graphics
		graphics.terminate();
		//terminate textures
		Texture::terminate();
		// terminate resource managers
		ResourceManager<Sprite>::terminate();
		ResourceManager<Font>::terminate();
		ResourceManager<Scene>::terminate();
		//delete camera
		delete Camera::current;
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