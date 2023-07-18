
#include "Application.h"

namespace ASEngine {

	Application::Application(Platform platform) {
		// set platform
		m_Platform = platform;

		// init application window
		Window::Init();

		// init ecs world
		World::Init();

		// init unique string manager
		UniqueStringManager::Init();

		// init resource managers
		//ResourceManager<Sprite>::Init();
		//Sprite::importAll();

		//ResourceManager<Font>::Init();
		//Font::importAll();

		Debug::Log("Application init complete");
	}

	Application::~Application()
	{
		World::Terminate();
		UniqueStringManager::Terminate();
		//ResourceManager<Sprite>::Terminate();
		//ResourceManager<Font>::Terminate();
		Window::Terminate();
	}

	void Application::Create(Platform platform) {
		if (s_Singleton)
			return;
		s_Singleton = new Application(platform);
	}

	void Application::IOnInputEvent(InputEvent &inputEvent) {
		// process event for each instance
	}

	void Application::Update(float delta) {
		// update here..
		World::GetSingleton()->Update(delta);
	}


	void Application::LoadProjectSettings() {
		//load json file
		File projectSettingsFile;
		projectSettingsFile.Open("project.settings.json", FileOpenMode::READ);
		std::string projectSettingsString = projectSettingsFile.ReadText();
		projectSettingsFile.Close();
		

		//parse to json
		nlohmann::json projectSettings = nlohmann::json::parse(projectSettingsString);
		
		// set project name
		std::string projectName = projectSettings["name"];
		Window::SetTitle(projectName);

		

		// set window size
		int windowWidth = projectSettings["window"]["size"]["width"];
		int windowHeight = projectSettings["window"]["size"]["height"];
		Window::SetSize(windowWidth, windowHeight);

		// set fullscreen mode
		bool windowIsFullscreen = projectSettings["window"]["fullscreen"];
		Window::SetFullscreen(windowIsFullscreen);
	}


} // ASEngine