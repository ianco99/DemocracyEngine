#pragma once

namespace DemoEngine_Renderer
{
	
	static class Renderer
	{
	private:
		unsigned int shader;

	public:
		Renderer();
		~Renderer();

		static Renderer* GetRender();
		static Renderer* RendererInstance;

		void RenderFrame();
		void Update();

		void CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize);
		void DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);

		void DrawShape(unsigned int& VAO);
	};
}