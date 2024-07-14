#include "ShaderSourceTest.h"

ShaderSourceTest::~ShaderSourceTest()
{
    
}

void ShaderSourceTest::Describe()
{
    // load resource
    Test("it loads shader source", [this]()
    {
        ASENGINE_REGISTER_RESOURCE_CLASS(ShaderSource);
        m_Source = ShaderSource::GetResourceClass().Load("shaders/default3D.vert"); 
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
            ASENGINE_EXPECT(identifierInfo.VectorSize == 3);
            ASENGINE_EXPECT(identifierInfo.Columns == 3);
            ASENGINE_EXPECT(identifierInfo.Offset == i * sizeof(Matrix3x3));
        }
    });

    // check for sampler 
    Test("it has sampler named Texture", [this]()
    {
        UniqueString samplerName{"Texture"};
        ASENGINE_EXPECT(m_Source->GetShaderParams().Samplers.find(samplerName) != m_Source->GetShaderParams().Samplers.end());

        // clean up necessaray be cause we registered the shader source class after shader source test causing
        m_Source = ResourceRef<ShaderSource>::NONE();
    });
}
