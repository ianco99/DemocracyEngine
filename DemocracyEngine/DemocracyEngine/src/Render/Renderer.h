#pragma once

#include "../Tools/Export.h"
#include "../Tools/stb_image.h"
#include <iostream>
#include "Shader.h"
#include "glew.h"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "../Tools/TextureImporter.h"
#include "../Window/Window.h"

using namespace  glm;
using namespace DemoEngine_Window;
using namespace DemoEngine_Tools;

namespace DemoEngine_Renderer
{
	
	static class EXPORT Renderer
	{
	private:
		unsigned int primitiveShader;
		unsigned int textureShader;
		TextureImporter textureImporter;
		
		mat4x4 proyection;
		mat4x4 view;

	public:
		Renderer();
		~Renderer();

		static Renderer* GetRender();
		static Renderer* RendererInstance;

		void RenderFrame();
		void Update();

		void CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize);
		void DrawShape(unsigned int& VAO, mat4x4 model, vec4 color, int sizeIndex);
		void DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);
		
		void CreateSprite(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize);
		void DrawTexture(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, unsigned int& idTexture);
		void BindTexture(const char* textureName, unsigned& textureID, bool filtureModeNearest);

	};
}
