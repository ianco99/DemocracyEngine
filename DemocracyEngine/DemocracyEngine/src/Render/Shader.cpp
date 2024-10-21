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

    unsigned int Shader::InitShader(string fileLocation)
    {
        ifstream stream(fileLocation);

        if (!stream.is_open())
        {
            cout << "Error, File shader with route: " + fileLocation + " doesn't exist " << endl;
        }
        else
        {
            cout << "File shader with route: " + fileLocation + " finded " << endl;
        }
        
        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        string line;

        stringstream _stringstream[2];

        ShaderType type = ShaderType::NONE;

        while (getline(stream, line))
        {
            if (line.find("#shader") != string::npos)
            {
                if (line.find("vertex") != string::npos)
                {
                    type = ShaderType::VERTEX;
                }

                else if (line.find("fragment") != string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }

            else
            {
                _stringstream[(int)type] << line << '\n';
            }

        }

        unsigned int value = CreateShader(_stringstream[0].str(), _stringstream[1].str());
        return value;
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
