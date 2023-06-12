
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
		//init resource managers
		ResourceManager<Sprite>::init();
		ResourceManager<Font>::init();
		ResourceManager<Scene>::init();
		// manually import some resources to try the new system
		// will be removed soon
		Image image;
		image.load("sprites/spr_run.png");

		Texture texture = Texture::load(image);

		Sprite sprite;
		sprite.load(texture, 6, vec2::zero());
		ResourceManager<Sprite>::getSingleton()->add("spr_run", sprite);

		Font font;
		font.load("fonts/RobotoCondensed-Regular.ttf", 24, 4, 4, 8);
		ResourceManager<Font>::getSingleton()->add("ft_default", font);

		Scene scene;
		scene.load("scenes/main.scene.json");
		ResourceManager<Scene>::getSingleton()->add("sc_main", scene);

		GameObject* obj = Instance::create("NewObject");
		obj->position = vec2{0.0f, 0.0f};
		//create default camera
		Camera::current = new Camera();

		Log::out("Application init complete");
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