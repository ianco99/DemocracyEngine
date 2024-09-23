#include "Renderer.h"

namespace DemoEngine_Renderer
{
	Renderer* Renderer::RendererInstance = nullptr;

	Renderer::Renderer()
	{
		RendererInstance = this;

		GLenum result = glewInit();

		if (result == GLEW_OK)
		{
			std::cout << "Renderer successfully created." << std::endl;
		}
		else
		{
			std::cout << "[RENDERER] Glew initialization error" << std::endl;
		}

		Shader* a = new Shader();

		string fragmentShader = a->ReadShaderFile("rsc/fragmentShader.DemoShader");
		string vertexShader = a->ReadShaderFile("rsc/vertexShader.DemoShader");
		
		shader = a->CreateShader(vertexShader, fragmentShader);
		glUseProgram(shader);
		delete a;


		proyection = ortho(0.0f, 1024.0f, 0.0f, 720.0f, 0.1f, 100.0f);
		vec3 cameraPosition = vec3(0, 0, 50);
		view = lookAt(cameraPosition, { 0,0,0 }, { 0,1,0 });
	}

	Renderer::~Renderer()
	{
		std::cout << "Deleted renderer." << std::endl;
	}

	void Renderer::Update()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void Renderer::CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize, int indexSize)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, indexs, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		std::cout << "Create new Shape." << std::endl;
	}

	void Renderer::DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		std::cout << "Delete Shape." << std::endl;
	}

	void Renderer::DrawShape(unsigned int& VAO, mat4x4 model, vec4 color, int sizeIndex)
	{
		glUseProgram(shader);
		
		unsigned int transformLoc = glGetUniformLocation(shader, "u_MVP");
		mat4 MVP = proyection * view * model;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(MVP));
		
		glBindVertexArray(VAO);
		
		int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, color.x, color.y, color.z, color.w);
		
		glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);
		glUseProgram(0);
	}

	Renderer* Renderer::GetRender()
	{
		return RendererInstance;
	}
}
