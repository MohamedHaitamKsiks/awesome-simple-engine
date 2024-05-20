#include "ShaderSourceTest.h"

void ShaderSourceTest::Describe()
{
    // register shader source 
    ResourceManager::GetInstance().RegisterResourceClass<ShaderSource>(UniqueString("ShaderSource"));

    // load resource
    Test("it loads shader source", [this]()
    {
        UniqueString shaderPath{"shaders/default3D.vert"};
        m_Source = ShaderSource::GetResourceClass().GetResource(shaderPath);
        
        ASENGINE_EXPECT(m_Source->GetReferenceName() == shaderPath); 
    });

    // check fro uniform buffer
    Test("it has a uniform buffer named Render", [this]()
    {
        // check if uniform buffer exists
        UniqueString renderBufferName{"Render"};
        const auto& uniformBuffers = m_Source->GetShaderParams().UniformBuffers; 

        ASENGINE_EXPECT(uniformBuffers.find(renderBufferName) != uniformBuffers.end());

        // check if uniform buffer have 3 mat4 fields
        const auto& renderBufferInfo = uniformBuffers.at(renderBufferName);
        ASENGINE_EXPECT(renderBufferInfo.Identifiers.size() == 3);

        // check binding
        ASENGINE_EXPECT(renderBufferInfo.Binding == 0);

        // list of expected field namesconst auto& fieldInfo
        UniqueString fieldNames[] = {
            UniqueString("Model"),
            UniqueString("View"),
            UniqueString("Projection")
        };

        // check if it has all fields and all of them are mat4
        const auto& identifiers = renderBufferInfo.Identifiers;
        for (int i = 0; i < 3; i++)
        {
            // has field
            ASENGINE_EXPECT(identifiers.find(fieldNames[i]) != identifiers.end());
            
            // check field type
            const auto& identifierInfo = identifiers.at(fieldNames[i]);
            
            ASENGINE_EXPECT(identifierInfo.Type == ShaderIdentifierType::FLOAT);
            ASENGINE_EXPECT(identifierInfo.VectorSize == 4);
            ASENGINE_EXPECT(identifierInfo.Columns == 4);
            ASENGINE_EXPECT(identifierInfo.Offset == i * sizeof(Matrix4x4));
        }
    });

    // check for sampler 
    Test("it has sampler named Texture", [this]()
    {
        UniqueString samplerName{"Texture"};
        ASENGINE_EXPECT(m_Source->GetShaderParams().Samplers.find(samplerName) != m_Source->GetShaderParams().Samplers.end());
    });
}
