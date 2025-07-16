#pragma once
#include "../Tools/Export.h"
#include <iostream>
#include "Shader.h"
#include "LightManager.h"
#include "glew.h"

#include "../Camera/Camera.h"
#include <glm/gtc/type_ptr.inl>

#include "../Tools/TextureImporter.h"
#include "../Window/Window.h"
#include "Material.h"
#include "../Mesh/Importer3D.h"

using namespace glm;
using namespace DemoEngine_Window;
using namespace DemoEngine_Tools;

namespace DemoEngine_Renderer
{
    static class EXPORT Renderer
    {
    private:
        TextureImporter textureImporter;
        Shader* primitiveShader;
        Shader* textureShader;
        Shader* lightShader;
        Shader* modelShader;

    public:
        Renderer(vec2 windowXY, Camera* camera, LightManager* light_manager);
        ~Renderer();

        static Renderer* GetRender();
        static Renderer* RendererInstance;

        Camera* MainCamera;
        LightManager* lightManager;
        void RenderFrame();
        void Update();

        void CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize);
        void DrawEntity2D(unsigned int& VAO, mat4x4 model, vec4 color, int sizeIndex) const;
        void DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);

        void CreateSprite(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize);
        void DrawTexture(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, unsigned int& idTexture);
        void DrawEntity3D(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, unsigned int idTexture, Material material);
        void DrawModel(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, vector<DemoEngine_Importer::Texture> textures, Material material);
        void BindTexture(const char* textureName, unsigned& textureID, GLint TextureFilter = GL_LINEAR);
    };
}