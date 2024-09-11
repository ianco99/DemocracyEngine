#include "Shader.h"

#include <fstream>
#include <glew.h>
#include <sstream>

namespace DemoEngine_Renderer
{
    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }

    string Shader::ReadShaderFile(string FileLocation)
    {
        ifstream file(FileLocation);

        if (!file.is_open())
        {
            cout << "Error, File shader with route: " + FileLocation + " doesn't exist " << endl;
            return " ";
        }
        else
        {
            cout << "File shader with route: " + FileLocation + " finded " << endl;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        std::cout << "Created shader." << std::endl;
        return program;
    }

    unsigned int Shader::CompileShader(unsigned int type, const string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* message = (char*)alloca(lenght * sizeof(char));
            glGetShaderInfoLog(id, lenght, &lenght, message);
            cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << endl;
            cout << message << endl;
            glDeleteShader(id);

            return 0;
        }
        return id;
    }
}
