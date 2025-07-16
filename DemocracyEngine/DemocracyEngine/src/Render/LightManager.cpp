#include "LightManager.h"

namespace DemoEngine_Renderer
{
    void LightManager::UploadToShader(Shader* shader)
    {
        shader->SetInt("dirLightCount", (int)directionalLights.size());
        for (int i = 0; i < directionalLights.size(); ++i)
        {
            std::string base = "dirLights[" + std::to_string(i) + "]";
            shader->SetVec3(base + ".direction", directionalLights[i].direction);
            shader->SetVec3(base + ".color", directionalLights[i].color);
        }

        shader->SetInt("pointLightCount", (int)pointLights.size());
        for (int i = 0; i < pointLights.size(); ++i)
        {
            std::string base = "pointLights[" + std::to_string(i) + "]";
            shader->SetVec3(base + ".position", pointLights[i].position);
            shader->SetVec3(base + ".color", pointLights[i].color);
            shader->SetFloat(base + ".constant", pointLights[i].constant);
            shader->SetFloat(base + ".linear", pointLights[i].linear);
            shader->SetFloat(base + ".quadratic", pointLights[i].quadratic);
            shader->SetFloat(base + ".intensity", pointLights[i].intensity);
        }

        shader->SetInt("spotLightCount", (int)spotLights.size());
        for (int i = 0; i < spotLights.size(); ++i)
        {
            std::string base = "spotLights[" + std::to_string(i) + "]";
            shader->SetVec3(base + ".position", spotLights[i].position);
            shader->SetVec3(base + ".direction", spotLights[i].direction);
            shader->SetVec3(base + ".color", spotLights[i].color);
            shader->SetFloat(base + ".cutOff", glm::cos(glm::radians(spotLights[i].cutOff)));
            shader->SetFloat(base + ".outerCutOff", glm::cos(glm::radians(spotLights[i].outerCutOff)));
            shader->SetFloat(base + ".constant", spotLights[i].constant);
            shader->SetFloat(base + ".linear", spotLights[i].linear);
            shader->SetFloat(base + ".quadratic", spotLights[i].quadratic);
            shader->SetFloat(base + ".intensity", spotLights[i].intensity);
        }
    }
}