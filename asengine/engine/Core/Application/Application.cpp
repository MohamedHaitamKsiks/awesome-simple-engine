
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
		// init graphics api
		GraphicsAPI::Init();
		// init renderer 2d
		Renderer2D::Init();
		// init renderer 33d
		Renderer3D::Init();
		// init texture manager
		TextureManager::Init();
		// init audio engine
		AudioEngine::Init();
		// init ecs world
		World::Init();
		// init module manager
		ModuleManager::Init();

		Debug::Log("Application init complete");
	}

	Application::~Application()
	{
		ResourceManager<Scene>::Terminate();
		World::Terminate();
		TerminateResourceManagers();
		ModuleManager::Terminate();
		Renderer3D::Terminate();
		Renderer2D::Terminate();
		Viewport::Terminate();
		AudioEngine::Terminate();
		Window::Terminate();
		UniqueStringManager::Terminate();
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
		ResourceManager<Audio>::Init("Audios");
		ResourceManager<Scene>::Init("Scenes");
	}

	void Application::TerminateResourceManagers()
	{
		ResourceManager<Shader>::Terminate();
		ResourceManager<Material>::Terminate();
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

		// clear screen
		GraphicsAPI::Clear();

		// draw 3d
		Renderer3D::Draw();

		// render world 2d
		Renderer2D::Begin();
		World::Render2D();
		Renderer2D::End(); 

		// render ui
		Renderer2D::BeginUI();
		World::UIRender2D();
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

		// set fixed time step
		Time::FixedTimeStep = projectSettings["fixedTimeStep"];

		// load main scene
		auto mainScenePath = std::string(projectSettings["mainScene"]);
		ResourceID sceneID = ResourceManager<Scene>::GetResourceID(mainScenePath);
		auto& mainScene = ResourceManager<Scene>::Get(sceneID);
		mainScene.Instantiate();
	}


} // ASEngine