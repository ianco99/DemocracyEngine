#pragma once
#include <glew.h>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "../Tools/Export.h"

using namespace std;

namespace DemoEngine_Renderer
{
    class EXPORT Shader
    {
    public:
        Shader(string fileLocation);
        ~Shader();

        void UseShader() const;
        static void UnuseShader();

        GLint GetUniformLocation(const string& name) const;

        void SetInt(const string& name, int value) const;
        void SetFloat(const string& name, float value) const;
        void SetVec2(const string& name, const glm::vec2& value) const;
        void SetVec3(const string& name, const glm::vec3& value) const;
        void SetVec4(const string& name, const glm::vec4& value) const;
        void SetMat3(const string& name, const glm::mat3& value) const;
        void SetMat4(const string& name, const glm::mat4& value) const;

    private:
        unsigned int shaderId;
        unsigned int InitShader(string fileLocation);
        unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
        unsigned int CompileShader(unsigned int type, const string& source);
    };
}