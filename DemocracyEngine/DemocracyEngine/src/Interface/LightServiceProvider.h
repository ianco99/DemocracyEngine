#pragma once
#include "ILightService.h"

class LightServiceProvider : public ILightService {
private:
    std::vector<Light> lights;
    static const size_t MAX_LIGHTS = 4;

public:
    const std::vector<Light>& GetLights() const override {
        return lights;
    }

    void AddLight(const Light& light) override {
        if (lights.size() >= MAX_LIGHTS) {
            lights.erase(lights.begin());
        }
        lights.push_back(light);
    }

    void ClearLights() override {
        lights.clear();
    }
};
