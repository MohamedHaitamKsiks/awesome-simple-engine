#include "HelloTriangle.h"

struct Vertex
{
    Vector2 Position;
    Color Modulate;
};

void HelloTriangle::Init()
{
    // create buffers
    auto& bufferClass = Buffer::GetResourceClass();
    m_VertexBuffer = bufferClass.New();
    m_IndexBuffer = bufferClass.New();

    m_VertexBuffer->Create(BufferType::ARRAY);
    m_IndexBuffer->Create(BufferType::INDEX);

    // set buffers data
    std::vector<Vertex> vertexData = {
        Vertex{Vector2{0.0f, 1.0f}, Color::GREEN()},
        Vertex{Vector2{1.0f, -1.0f}, Color::RED()},
        Vertex{Vector2{-1.0f, -1.0f}, Color::BLUE()}
    };
    m_VertexBuffer->SetData(vertexData.data(), vertexData.size() * sizeof(Vertex));

    std::vector<uint32_t> indices = {0, 1, 2};
    m_IndexBuffer->SetData(indices.data(), indices.size() * sizeof(uint32_t));

    // craete shader
    m_Shader = Shader::GetResourceClass().Load("assets:://shaders/default.shader.json");

}

void HelloTriangle::Update(float delta)
{
    auto& renderer = Renderer::GetInstance();

    renderer.Begin();

    renderer.Clear();

    renderer.BindShader(m_Shader);

    renderer.BindVertexBuffer(m_VertexBuffer, 0);
    renderer.BindIndexBuffer(m_IndexBuffer);

    renderer.DrawElements(3);

    renderer.End();
}
