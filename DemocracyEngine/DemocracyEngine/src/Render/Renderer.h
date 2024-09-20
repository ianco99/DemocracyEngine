#pragma once

#include <iostream>
#include "Shader.h"
#include "glew.h"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "../Window/Window.h"

using namespace  glm;
using namespace DemoEngine_Window;

namespace DemoEngine_Renderer
{
	
	static class Renderer
	{
	private:
		unsigned int shader;
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
		void DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);

		void DrawShape(unsigned int& VAO, mat4x4 model, vec4 color, int sizeIndex);
	};
}
