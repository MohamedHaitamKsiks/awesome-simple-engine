#include "TextRenderer2D.h"

EXPORT(TextRenderer2D, FontName, Text, Modulate)

void TextRenderer2D::OnCreate()
{
    FontID = ResourceManager<Font>::GetResourceId(FontName);
}