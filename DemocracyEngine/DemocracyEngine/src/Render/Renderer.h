#pragma once

namespace DemoEngine_Renderer
{
	

	static class Renderer
	{
	private:

	public:
		Renderer();
		~Renderer();

		static Renderer* GetRender();
		static Renderer* RendererInstance;

		void RenderFrame();
		void Update();

		void CreateShape(unsigned int& VBO, float vertex[]);
		void DrawShape();
	};
}