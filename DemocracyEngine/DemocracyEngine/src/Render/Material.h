#pragma once
#include <glm/vec3.hpp>

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material()
    {
        ambient = glm::vec3(0.0f, 0.0f, 0.0f);
        diffuse = glm::vec3(0.5f, 0.0f, 0.0f);
        specular = glm::vec3(0.7f, 0.6f, 0.6f);
        shininess = 0.0f;
    }

    Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Shininess)
    {
        ambient = Ambient;
        diffuse = Diffuse;
        specular = Specular;
        shininess = Shininess;
    }
};

const Material DefaultMaterial(
    glm::vec3(0.2f, 0.2f, 0.2f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    32.0f
);

const Material Emerald(
    glm::vec3(0.0215f, 0.1745f, 0.0215f),
    glm::vec3(0.07568f, 0.61424f, 0.07568f),
    glm::vec3(0.633f, 0.727811f, 0.633f),
    76.8f
);

const Material Jade(
    glm::vec3(0.135f, 0.2225f, 0.1575f),
    glm::vec3(0.54f, 0.89f, 0.63f),
    glm::vec3(0.316228f, 0.316228f, 0.316228f),
    12.8f
);

const Material Obsidian(
    glm::vec3(0.05375f, 0.05f, 0.06625f),
    glm::vec3(0.18275f, 0.17f, 0.22525f),
    glm::vec3(0.332741f, 0.328634f, 0.346435f),
    38.4f
);

const Material Pearl(
    glm::vec3(0.25f, 0.20725f, 0.20725f),
    glm::vec3(1.0f, 0.829f, 0.829f),
    glm::vec3(0.296648f, 0.296648f, 0.296648f),
    11.264f
);

const Material Ruby(
    glm::vec3(0.1745f, 0.01175f, 0.01175f),
    glm::vec3(0.61424f, 0.04136f, 0.04136f),
    glm::vec3(0.727811f, 0.626959f, 0.626959f),
    76.8f
);

const Material Turquoise(
    glm::vec3(0.1f, 0.18725f, 0.1745f),
    glm::vec3(0.396f, 0.74151f, 0.69102f),
    glm::vec3(0.297254f, 0.30829f, 0.306678f),
    12.8f
);

const Material Brass(
    glm::vec3(0.329412f, 0.223529f, 0.027451f),
    glm::vec3(0.780392f, 0.568627f, 0.113725f),
    glm::vec3(0.992157f, 0.941176f, 0.807843f),
    27.8974f
);

const Material Bronze(
    glm::vec3(0.2125f, 0.1275f, 0.054f),
    glm::vec3(0.714f, 0.4284f, 0.18144f),
    glm::vec3(0.393548f, 0.271906f, 0.166721f),
    25.6f
);

const Material Chrome(
    glm::vec3(0.25f, 0.25f, 0.25f),
    glm::vec3(0.4f, 0.4f, 0.4f),
    glm::vec3(0.774597f, 0.774597f, 0.774597f),
    76.8f
);

const Material Copper(
    glm::vec3(0.19125f, 0.0735f, 0.0225f),
    glm::vec3(0.7038f, 0.27048f, 0.0828f),
    glm::vec3(0.256777f, 0.137622f, 0.086014f),
    12.8f
);

const Material Gold(
    glm::vec3(0.24725f, 0.1995f, 0.0745f),
    glm::vec3(0.75164f, 0.60648f, 0.22648f),
    glm::vec3(0.628281f, 0.555802f, 0.366065f),
    51.2f
);

const Material Silver(
    glm::vec3(0.19225f, 0.19225f, 0.19225f),
    glm::vec3(0.50754f, 0.50754f, 0.50754f),
    glm::vec3(0.508273f, 0.508273f, 0.508273f),
    51.2f
);

const Material BlackPlastic(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.01f, 0.01f, 0.01f),
    glm::vec3(0.50f, 0.50f, 0.50f),
    32.0f
);

const Material CyanPlastic(
    glm::vec3(0.0f, 0.1f, 0.06f),
    glm::vec3(0.0f, 0.50980392f, 0.50980392f),
    glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
    32.0f
);

const Material GreenPlastic(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.1f, 0.35f, 0.1f),
    glm::vec3(0.45f, 0.55f, 0.45f),
    32.0f
);

const Material RedPlastic(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 0.0f, 0.0f),
    glm::vec3(0.7f, 0.6f, 0.6f),
    32.0f
);

const Material WhitePlastic(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.55f, 0.55f, 0.55f),
    glm::vec3(0.70f, 0.70f, 0.70f),
    32.0f
);

const Material YellowPlastic(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 0.5f, 0.0f),
    glm::vec3(0.60f, 0.60f, 0.50f),
    32.0f
);

const Material BlackRubber(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(0.01f, 0.01f, 0.01f),
    glm::vec3(0.4f, 0.4f, 0.4f),
    10.0f
);

const Material CyanRubber(
    glm::vec3(0.0f, 0.05f, 0.05f),
    glm::vec3(0.4f, 0.5f, 0.5f),
    glm::vec3(0.04f, 0.7f, 0.7f),
    10.0f
);

const Material GreenRubber(
    glm::vec3(0.0f, 0.05f, 0.0f),
    glm::vec3(0.4f, 0.5f, 0.4f),
    glm::vec3(0.04f, 0.7f, 0.04f),
    10.0f
);

const Material RedRubber(
    glm::vec3(0.05f, 0.0f, 0.0f),
    glm::vec3(0.5f, 0.4f, 0.4f),
    glm::vec3(0.7f, 0.04f, 0.04f),
    10.0f
);

const Material WhiteRubber(
    glm::vec3(0.05f, 0.05f, 0.05f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.7f, 0.7f, 0.7f),
    10.0f
);

const Material YellowRubber(
    glm::vec3(0.05f, 0.05f, 0.0f),
    glm::vec3(0.5f, 0.5f, 0.4f),
    glm::vec3(0.7f, 0.7f, 0.04f),
    10.0f
);