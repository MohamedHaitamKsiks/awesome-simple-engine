#ifndef __ASENGINE_VERTEX_INPUT_DESCRIPTOR_H
#define __ASENGINE_VERTEX_INPUT_DESCRIPTOR_H

#include <vector>

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceSerialization.h"
#include "Resource/ResourceDefinition.h"

#include "VertexInput.h"



namespace ASEngine
{
    // Describe the layout of the vertex input
    class  VertexInputDescriptor : public Resource
    {
    ASENGINE_DEFINE_RESOURCE(VertexInputDescriptor);
    ASENGINE_SERIALIZE_RESOURCE(VertexInputDescriptor);
    public:
        VertexInputDescriptor() = default;
        virtual ~VertexInputDescriptor() {} // make it polymorphic

        // create input descriptor from list of layouts
        void Create(const std::vector<VertexInputLayout>& layouts);

        inline const std::vector<VertexInputLayout>& GetVertexInputLayouts() const
        {
            return m_VertexInputLayouts;
        }

    protected:
        virtual void CreateImp(const std::vector<VertexInputLayout>& layouts) = 0;

    private:
        friend class Serializer;
        std::vector<VertexInputLayout> m_VertexInputLayouts{};
    };
} // namespace ASEngine


#endif // __ASENGINE_VERTEX_INPUT_DESCRIPTOR_H