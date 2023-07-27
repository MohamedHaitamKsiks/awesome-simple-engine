
#include "Application.h"

namespace ASEngine {

	Application::Application(Platform platform) {
		// set platform
		m_Platform = platform;

		// init unique string manager
		UniqueStringManager::Init();

		// init application window
		Window::Init();

		// init viewport
		Viewport::Init();

		// init renderer 2d
		Renderer2D::Init();

		// init texture manager
		TextureManager::Init();

		// init ecs world
		World::Init();

		// init resource managers
		ResourceManager<Shader>::Init();
		ResourceManager<Material>::Init();
		ResourceManager<Sprite>::Init();
		ResourceManager<Font>::Init();

		Debug::Log("Application init complete");
	}

	Application::~Application()
	{
		World::Terminate();
		UniqueStringManager::Terminate();
		ResourceManager<Shader>::Terminate();
		ResourceManager<Material>::Terminate();
		ResourceManager<Sprite>::Terminate();
		ResourceManager<Font>::Terminate();
		Renderer2D::Terminate();
		Viewport::Terminate();
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
		World::Update(delta);
	
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
		if (GetSingleton()->m_Platform != Platform::ANDROID_DEVICES)
			Window::SetSize(windowWidth, windowHeight);

		// set fullscreen mode
		bool windowIsFullscreen = projectSettings["window"]["fullscreen"];
		if (GetSingleton()->m_Platform != Platform::ANDROID_DEVICES)
			Window::SetFullscreen(windowIsFullscreen);
	
		// set view port
		int viewportWidth = projectSettings["viewport"]["size"]["width"];
		int viewportHeight = projectSettings["viewport"]["size"]["height"];
		Viewport::SetSize(viewportWidth, viewportHeight);
	}


} // ASEngine