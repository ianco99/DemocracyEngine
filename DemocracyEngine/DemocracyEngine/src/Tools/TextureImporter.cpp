#include "../Tools/TextureImporter.h"

namespace DemoEngine_Tools
{
    unsigned char* TextureImporter::GetTexture(const char* path, int &m_Width, int &m_Height, int &m_BPP)
    {
        unsigned char* m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

        return m_LocalBuffer;
    }
}