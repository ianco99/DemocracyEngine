#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    Kposition = vec3{0, 0, 10};
    Kscale = vec3{20, 20, 20};
    Krotation = vec3{0, 0, 0};
    Kcolor = vec4{0, 0, 1, 1};

    
    const char* path = "rsc/SpritesAnimations/Orange.png";

    pCube = new Cube(Kposition, Krotation, Kscale, path);
    pCube->setMaterial(BlackPlastic);

    path = "rsc/Mesh/Jester.fbx";
    jester = new Model3D(vec3(500, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), path, false);

#pragma region Room
    path = "rsc/SpritesAnimations/White.png";
    floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);

    float halfSize = 2000.0f;
    float wallHeight = 500.0f;
    float wallThickness = 5.0f;

    path = "rsc/SpritesAnimations/Orange.png";

    wall1 = new Cube(vec3{-halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness},
                     path);
    wall1->setMaterial(Turquoise);

    wall2 = new Cube(vec3{halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness},
                     path);
    wall2->setMaterial(Brass);

    wall3 = new Cube(vec3{0, wallHeight / 2 - 100, -halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness},
                     path);
    wall3->setMaterial(Copper);

    wall4 = new Cube(vec3{0, wallHeight / 2 - 100, halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness},
                     path);
    wall4->setMaterial(WhitePlastic);

    Top = new Cube(vec3{0, wallHeight - 100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    Top->setMaterial(RedPlastic);
#pragma endregion

    timer = new DemoEngine_Animations::DemoTimer();

    float offset = halfSize * 0.75f;

    glm::vec3 corners[4] = {
        glm::vec3(-offset, 0, -offset),
        glm::vec3(offset, 0, -offset),
        glm::vec3(-offset, 0, offset),
        glm::vec3(offset, 0, offset)
    };

    glm::vec3 colors[4] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(1.0f, 1.0f, 0.0f)
    };

    for (int i = 0; i < 4; i++)
    {
        PointLight pl;
        pl.position = corners[i] + glm::vec3(0, 100, 0);
        pl.color = colors[i];
        pl.intensity = 100.0f;
        pl.constant = 1.0f;
        pl.linear = 0.012f;
        pl.quadratic = 0.007f;

        lightManager->pointLights.push_back(pl);
    }

    PointLight pl;
    pl.position = glm::vec3(0, 100, 0);
    pl.color = glm::vec3(0.0f, 0.0f, 5.0f);
    pl.intensity = 50.0f;
    pl.constant = 5.0f;
    pl.linear = 0.07f;
    pl.quadratic = 0.002f;
    lightManager->pointLights.push_back(pl);

    SpotLight spotLight;
    spotLight.position = glm::vec3(0, 50, 2000);
    spotLight.direction = MainCamera->GetCameraFoward();
    spotLight.color = glm::vec3(1.0f);
    spotLight.cutOff = 20.0f;
    spotLight.outerCutOff = 30.0f;
    spotLight.constant = 1.0f;
    spotLight.linear = 0.007f;
    spotLight.quadratic = 0.0002f;
    spotLight.intensity = 900.0f;
    lightManager->spotLights.push_back(spotLight);

    lightManager->directionalLights.push_back({glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.3f)});

    path = "rsc/Knuckles_Sprite_Sheet.png";
    knuckles = new DemoEngine_Entities::Sprite(path, 646, 473, 2, 434, 33, 38, Kcolor, Kposition, Kscale, Krotation,
                                               true);


    walkAnim = new Animation();
    walkAnim->AddFrame(339, 388, 33, 38, 646, 473, 1, 3, 9);

    ballAnim = new Animation();
    ballAnim->AddFrame(1, 314, 31, 28, 646, 473, 1, 6, 1);

    idleAnim = new Animation();
    idleAnim->AddFrame(2, 434, 33, 38, 646, 473, 1, 1);

    knuckles->AddAnimation(walkAnim);
}

void EarthGame::Update()
{
    vec3 translation = vec3(0, 0, 0);

    if (input->IsKeyPressed(GLFW_KEY_S))
    {
        translation = vec3(0, 0, -1);
        knuckles->AddAnimation(walkAnim);
    }
    else if (input->IsKeyPressed(GLFW_KEY_W))
    {
        translation = vec3(0, 0, 1);
        knuckles->AddAnimation(walkAnim);
    }
    else if (input->IsKeyPressed(GLFW_KEY_A))
    {
        translation = vec3(-1, 0, 0);
        knuckles->setRotationY(-180);

        knuckles->AddAnimation(walkAnim);
    }
    else if (input->IsKeyPressed(GLFW_KEY_D))
    {
        knuckles->setRotationY(1);
        translation = vec3(1, 0, 0);
        knuckles->AddAnimation(walkAnim);
    }
    else if (input->IsKeyPressed(GLFW_KEY_E))
    {
        translation = vec3(0, 1, 0);
        knuckles->AddAnimation(walkAnim);
    }
    else if (input->IsKeyPressed(GLFW_KEY_R))
    {
        translation = vec3(0, -1, 0);
        knuckles->AddAnimation(walkAnim);
    }
    else
    {
        knuckles->AddAnimation(idleAnim);
    }

    if (input->IsKeyPressed(GLFW_KEY_SPACE))
    {
        knuckles->AddAnimation(ballAnim);
    }

    knuckles->Translate(translation);

    knuckles->Update(timer);

    //knuckles->Draw();
    pCube->Draw();
    jester->Draw();
    
    floor->Draw();
    wall1->Draw();
    wall2->Draw();
    wall3->Draw();
    wall4->Draw();
    Top->Draw();
}

void EarthGame::DeInit()
{
    delete knuckles;
    delete idleAnim;
    delete walkAnim;
    delete ballAnim;

    delete pCube;
}
