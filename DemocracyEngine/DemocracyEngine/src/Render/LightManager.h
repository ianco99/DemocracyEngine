#pragma once
#include <vector>
#include <string>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"

namespace DemoEngine_Renderer
{
    struct DirLight
    {
        glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 color = glm::vec3(1.0f);
    };

    struct PointLight
    {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 color = glm::vec3(1.0f);
        
        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;
        
        float intensity = 50.0f;
    };

    struct SpotLight
    {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 color = glm::vec3(1.0f);
        
        float cutOff = 12.5f;        
        float outerCutOff = 15.0f;
        
        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;
        
        float intensity = 50.0f;
    };

    class LightManager {
    public:
        std::vector<DirLight> directionalLights;
        std::vector<PointLight> pointLights;
        std::vector<SpotLight> spotLights;

        void UploadToShader(Shader* shader);
    };
}