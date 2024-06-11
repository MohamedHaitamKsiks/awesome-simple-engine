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
    class VertexInputDescriptor: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(VertexInputDescriptor);
    ASENGINE_SERIALIZE_RESOURCE(VertexInputDescriptor);
    public:
        VertexInputDescriptor() = default;
        ~VertexInputDescriptor() {}

        inline const std::vector<VertexInputLayout>& GetVertexInputLayouts() const
        {
            return m_VertexInputLayouts;
        }

    private:
        friend class Serializer;
        std::vector<VertexInputLayout> m_VertexInputLayouts{};
    };
} // namespace ASEngine


#endif // __ASENGINE_VERTEX_INPUT_DESCRIPTOR_H