#pragma once
#include "ILightService.h"
#include "LightServiceProvider.h"

class ServiceProvider {
private:
    static ILightService* lightProvider;

public:
    static ILightService* GetLightProvider() {
        if (lightProvider == nullptr) {
            lightProvider = new LightServiceProvider();
        }
        return lightProvider;
    }
};
