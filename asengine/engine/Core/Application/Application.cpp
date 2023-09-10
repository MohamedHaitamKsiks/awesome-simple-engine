
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
		// init audio engine
		AudioEngine::Init();
		// init ecs world
		World::Init();

		Debug::Log("Application init complete");
	}

	Application::~Application()
	{
		World::Terminate();
		UniqueStringManager::Terminate();
		TerminateResourceManagers();
		Renderer2D::Terminate();
		Viewport::Terminate();
		AudioEngine::Terminate();
		Window::Terminate();
	}

	void Application::Create(Platform platform) {
		if (s_Singleton)
			return;
		s_Singleton = new Application(platform);
	}

	void Application::InitResourceManagers()
	{
		ResourceManager<Shader>::Init("Shaders");
		ResourceManager<Material>::Init("Materials");
		ResourceManager<Sprite>::Init("Sprites");
		ResourceManager<Font>::Init("Fonts");
		ResourceManager<Audio>::Init("Audios");
		ResourceManager<Scene>::Init("Scenes");

		Debug::Log("Init resource manages");
	}

	void Application::TerminateResourceManagers()
	{
		ResourceManager<Shader>::Terminate();
		ResourceManager<Material>::Terminate();
		ResourceManager<Sprite>::Terminate();
		ResourceManager<Font>::Terminate();
		ResourceManager<Scene>::Terminate();
		ResourceManager<Audio>::Terminate();
	}


	void Application::Update(float delta) {
		// process input
		for (auto& event: GetSingleton()->m_InputEventQueue)
		{
			World::ProcessInputEvent(event);
		}
		GetSingleton()->m_InputEventQueue.Clear();

		// update here..
		World::Update(delta);

		// render world 2d
		Renderer2D::Begin();
		World::Render2D();
		Renderer2D::End(); 
	
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

		// set view port
		int viewportWidth = projectSettings["viewport"]["size"]["width"];
		int viewportHeight = projectSettings["viewport"]["size"]["height"];
		Viewport::SetSize(viewportWidth, viewportHeight);

		// set window size
		int windowWidth = projectSettings["window"]["size"]["width"];
		int windowHeight = projectSettings["window"]["size"]["height"];
		if (GetSingleton()->m_Platform != Platform::ANDROID_DEVICES)
			Window::SetSize(windowWidth, windowHeight);

		// set fullscreen mode
		bool windowIsFullscreen = projectSettings["window"]["fullscreen"];
		if (GetSingleton()->m_Platform != Platform::ANDROID_DEVICES)
			Window::SetFullscreen(windowIsFullscreen);

		// load main scene
		UniqueString mainScenePath = UniqueString(std::string(projectSettings["mainScene"]));
		ResourceID sceneID = ResourceManager<Scene>::GetResourceId(UniqueString(mainScenePath));
		Scene& mainScene = ResourceManager<Scene>::Get(sceneID);
		mainScene.Instantiate();
	}


} // ASEngine