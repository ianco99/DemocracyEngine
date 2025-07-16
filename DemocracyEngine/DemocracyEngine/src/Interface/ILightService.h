#pragma once
#include <vector>
#include "Light.h"

class ILightService {
public:
    virtual const std::vector<Light>& GetLights() const = 0;
    virtual void AddLight(const Light& light) = 0;
    virtual void ClearLights() = 0;
    virtual ~ILightService() = default;
};
