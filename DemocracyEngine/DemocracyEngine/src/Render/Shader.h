#pragma once
#include <iostream>
#include "../Tools/Export.h"

using namespace std;

namespace DemoEngine_Renderer
{
	class EXPORT Shader
	{
	public:
		Shader();
		~Shader();
		string ReadShaderFile(string FileLocation);
		unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const string& source);

	private:

	};


}