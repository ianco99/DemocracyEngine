#include "Shader.h"

#include <fstream>
#include <glew.h>
#include <sstream>

namespace DemoEngine_Renderer
{
    Shader::Shader(string fileLocation)
    {
        try
        {
            shaderId = InitShader(fileLocation);
        }
        catch (const std::exception& e)
        {
            cerr << e.what() << endl;
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(shaderId);
    }

    void Shader::UseShader() const
    {
        glUseProgram(shaderId);
    }

    void Shader::UnuseShader()
    {
        glUseProgram(0);
    }

    GLint Shader::GetUniformLocation(const string& name) const
    {
        GLint location = glGetUniformLocation(shaderId, name.c_str());
        return location;
    }

    void Shader::SetInt(const string& name, int value) const
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const string& name, float value) const
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetVec2(const string& name, const glm::vec2& value) const
    {
        glUniform2f(GetUniformLocation(name), value.x, value.y);
    }

    void Shader::SetVec3(const string& name, const glm::vec3& value) const
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::SetVec4(const string& name, const glm::vec4& value) const
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat3(const string& name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::SetMat4(const string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
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