#include "ViewportExample.h"

struct Vertex
{
    Vector2 Position;
    Vector2 UV;
};

Vector2 ViewportExample::Lerp(const Vector2 &a, const Vector2 &b, float t)
{
    return a * (1.0f - t) + b * t;
}

void ViewportExample::Init()
{
    // create viewport
    m_Viewport = Viewport::GetResourceClass().New();
    m_Viewport->Create(320, 180, 1);

    // load materials
    auto& materialClass = Material::GetResourceClass();
    
    m_DefaultMaterial = materialClass.Load("materials/default.material.json");
    m_WavesMaterial = materialClass.Load("materials/waves.material.json");
    
    // create buffers
    auto& bufferClass = Buffer::GetResourceClass();

    // create triangle vertex buffer
    std::vector<Vertex> triangleVertexData = {
        Vertex{Vector2{0.0f, 1.0f}, Vector2{0.0f, 1.0f}},
        Vertex{Vector2{1.0f, -1.0f}, Vector2{1.0f, 1.0f}},
        Vertex{Vector2{-1.0f, -1.0f}, Vector2{1.0f, 0.0f}}
    };
    std::vector<uint32_t> triangleIndices = {0, 1, 2};
    
    m_TriangleVertexBuffer = bufferClass.New();
    m_TriangleVertexBuffer->Create(BufferType::ARRAY);
    m_TriangleVertexBuffer->SetData(triangleVertexData.data(), triangleVertexData.size() * sizeof(Vertex));

    m_TriangleIndexBuffer = bufferClass.New();
    m_TriangleIndexBuffer->Create(BufferType::INDEX);
    m_TriangleIndexBuffer->SetData(triangleIndices.data(), triangleIndices.size() * sizeof(uint32_t));

    // create rectangle vertex buffer
    std::vector<Vertex> rectangleVertexData = {
        Vertex{Vector2{-1.0f, 1.0f}, Vector2{0.0f, 1.0f}},
        Vertex{Vector2{1.0f, 1.0f}, Vector2{1.0f, 1.0f}},
        Vertex{Vector2{1.0f, -1.0f}, Vector2{1.0f, 0.0f}},
        Vertex{Vector2{-1.0f, -1.0f}, Vector2{0.0f, 0.0f}},
    };
    std::vector<uint32_t> rectangleIndices = {0, 1, 2, 2, 3, 0};

    m_RectangleVertexBuffer = bufferClass.New();
    m_RectangleVertexBuffer->Create(BufferType::ARRAY);
    m_RectangleVertexBuffer->SetData(rectangleVertexData.data(), rectangleVertexData.size() * sizeof(Vertex));

    m_RectangleIndexBuffer = bufferClass.New();
    m_RectangleIndexBuffer->Create(BufferType::INDEX);
    m_RectangleIndexBuffer->SetData(rectangleIndices.data(), rectangleIndices.size() * sizeof(uint32_t));
    
}

void ViewportExample::Update(float delta)
{
    m_Timer += delta;

    auto& renderer = Renderer::GetInstance();
    
    // render to viewport
    renderer.Begin(m_Viewport);
    renderer.Clear();

    renderer.BindMaterial(m_DefaultMaterial);

    renderer.BindVertexBuffer(m_TriangleVertexBuffer, 0);
    renderer.BindIndexBuffer(m_TriangleIndexBuffer);

    renderer.DrawElements(3);

    renderer.End();

    // render to screen
    renderer.Begin();
    renderer.Clear();

    m_WavesMaterial->SetShaderParam("ScreenTexture", m_Viewport->GetTexture(0));

    // pinch position
    Vector2 pinchPosition = m_MousePosition;

    pinchPosition.x /= static_cast<float>(Display::GetInstance().GetWindowWidth());
    pinchPosition.y /= static_cast<float>(Display::GetInstance().GetWindowHeight());
    pinchPosition.y = 1.0f - pinchPosition.y;

    m_MousePosition = Lerp(m_MousePosition, m_TargetMousePosition, delta * 10.0f);

    // send wave data
    m_WavesMaterial->SetShaderParam("Waver", "Time", m_Timer);
    m_WavesMaterial->SetShaderParam("Waver", "Pos", pinchPosition);

    renderer.BindMaterial(m_WavesMaterial);

    renderer.BindVertexBuffer(m_RectangleVertexBuffer, 0);
    renderer.BindIndexBuffer(m_RectangleIndexBuffer);

    renderer.DrawElements(6);

    renderer.End();
}

void ViewportExample::OnInputEvent(const InputEvent &event)
{
    if (event.GetType() == InputEventType::KEYBOARD)
    {
        const auto& keyEvent = event.Get<InputEventKeyboard>();
        if (keyEvent.Code == Keycode::KEY_SPACE && keyEvent.Pressed)
        {
            auto& display = Display::GetInstance();
            display.SetFullscreen(!display.IsFullscreen());
        }
    }

    else if (event.GetType() == InputEventType::MOUSE_MOVE && m_MouseDown)
    {
        const auto& mouseMoveEvent = event.Get<InputEventMouseMove>();
        m_TargetMousePosition = mouseMoveEvent.Position;
    }

    else if (event.GetType() == InputEventType::MOUSE_BUTTON)
    {
        const auto &mouseButtonEvent = event.Get<InputEventMouseButton>();
        m_MouseDown = mouseButtonEvent.Pressed;
        if (mouseButtonEvent.Pressed && mouseButtonEvent.Button == MouseButton::LEFT)
        {
            m_TargetMousePosition = mouseButtonEvent.Position;
        }
    }
}

void ViewportExample::Terminate()
{
}
