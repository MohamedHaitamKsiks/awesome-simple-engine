#pragma once
#include "ASEngine.h"

using namespace ASEngine;

UNIT_TEST(ShaderManagerTest, 
{
    // load spirv
    SpirvBinary spirv{};

    File spirvFile;
    spirvFile.Open("shaders/test.spv", FileOpenMode::READ);

    size_t spirvSize = spirvFile.GetSize() / sizeof(uint32_t);
    auto spirvData = std::make_unique<uint32_t[]>(spirvSize);
    spirvFile.Read( reinterpret_cast<char*>(spirvData.get()) );

    for (int i = 0; i < spirvSize; i++) 
    {
        spirv.push_back(spirvData[i]);
    }

    spirvFile.Close();
    // end loading spirv file

    UNIT_TEST_CASE("It should load spirv file", 
    {
        EXPECT(spirv.size() == spirvSize);
    });

    // start tests
    ShaderManager* shaderManager = Renderer::GetShaderManager();
    ShaderID shaderID = shaderManager->Create(spirv, ShaderType::VERTEX);
    UniqueString paramName = UniqueString("Params");

    UNIT_TEST_CASE("It should create shader", 
    {
        EXPECT(shaderID == 0);
    });

    auto& shaderInfo = shaderManager->GetShaderInfo(shaderID);

    UNIT_TEST_CASE("It should have one uniform buffer named 'Params'", 
    {
        EXPECT(shaderInfo.Type == ShaderType::VERTEX);
        EXPECT(shaderInfo.UniformBuffers.size() == 1);
        EXPECT(shaderInfo.UniformBuffers.find(paramName) != shaderInfo.UniformBuffers.end());
    });

    auto &uniformBuffer = shaderInfo.UniformBuffers[paramName];

    UNIT_TEST_CASE("uniform buffer 'Params' should be of size 108 * sizeof(floats)", 
    {
        EXPECT(uniformBuffer.Size == 108 * sizeof(float));
    });

    auto& identifiers = uniformBuffer.Identifiers;

    UniqueString viewName = UniqueString("View");
    UniqueString cameraName = UniqueString("Camera");

    UNIT_TEST_CASE("Uniform Buffer 'Params' should have 2 identifiers View and Camera", 
    {
        EXPECT(identifiers.size() == 2);

        EXPECT(identifiers.find(viewName) != identifiers.end());
        EXPECT(identifiers.find(cameraName) != identifiers.end());
    });

    auto& viewIdentifier = identifiers[viewName];
    auto& cameraIdentifier = identifiers[cameraName];

    UNIT_TEST_CASE("Identifier View should have offset 0",
    {
        EXPECT(viewIdentifier.Offset == 0);
    });

    UNIT_TEST_CASE("Identifier Camera should have offset 12 * sizeof(float)",
    {
        EXPECT(cameraIdentifier.Offset == 12 * sizeof(float));
    });

    UNIT_TEST_CASE("Identifier View has valid type", 
    {
        EXPECT(viewIdentifier.Type == ShaderIdentifierType::FLOAT);
        EXPECT(viewIdentifier.VectorSize == 3);
        EXPECT(viewIdentifier.Columns == 3);
        EXPECT(viewIdentifier.ArrayDimentions.GetSize() == 0);
    });

    UNIT_TEST_CASE("Identifier Camera has valid type",
    {
        EXPECT(cameraIdentifier.Type == ShaderIdentifierType::FLOAT);
        EXPECT(cameraIdentifier.VectorSize == 3);
        EXPECT(cameraIdentifier.Columns == 3);
        EXPECT(cameraIdentifier.ArrayDimentions.GetSize() == 2);
        EXPECT(cameraIdentifier.ArrayDimentions[1] == 2);
        EXPECT(cameraIdentifier.ArrayDimentions[0] == 4);
    });
});
