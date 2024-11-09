#pragma once
#include "../Tools/Export.h"
#include "stb_image.h"
#include <string>

using namespace std;

namespace DemoEngine_Tools
{
    class EXPORT TextureImporter
    {
    private:

    public:

        unsigned char* GetTexture(const char* path, int &m_Width, int &m_Height, int &m_BPP);
    };

}