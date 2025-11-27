#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    testScene = new Scene();
    
    Kposition = vec3{0, 0, 100};
    Kscale = vec3{20, 20, 20};
    Krotation = vec3{0, 0, 0};
    Kcolor = vec4{0, 0, 1, 1};

    MainCamera->SetCameraPosition(vec3{0, 100, 150});

    const char* path = "rsc/SpritesAnimations/Orange.png";

    pCube = new Cube(Kposition, Krotation, Kscale, path);
    pCube->setMaterial(BlackPlastic);

    path = "rsc/Mesh/shield.fbx";
    shield = new Model3D(vec3(100, 0, 300), vec3(0, 0, 0), vec3(5, 5, 5), path, false);

    path = "rsc/Mesh/BikeBig.fbx";
    bike = new Model3D(vec3{700, 40, 900}, vec3{0, 0, 0}, vec3{2, 2, 2}, path, false);
    bike->AddTexture("texture_baseColor", "rsc/Mesh/White.png", false, true);
    bike->setMaterial(WhitePlastic);
    bike->transform->SetLocalScale(vec3{100, 60, 60});
    bike->transform->SetLocalRotation(vec3(-90, 0, 0));
    bike->drawWireBox = true;
    
    path = "rsc/Mesh/masterSword.fbx";
    mSword = new Model3D(vec3(900, 2, -600), vec3(0, 0, 0), vec3(10, 10, 10), path, false);

    path = "rsc/Mesh/cake_texturizar.fbx";
    cake = new Model3D(vec3(200, 2, 100), vec3(0, 0, 0), vec3(0.5f, 0.5f, 0.5f), path, false);
    cake->AddTexture("texture_baseColor", "rsc/Texturas/T_cake_Base_color.png", false, true);

    path = "rsc/Mesh/bspPlanesNew4.fbx";
    Model3D* planes = new Model3D(vec3{0, 0, 0}, vec3{0, 0, 0}, vec3{1, 0.2, 1}, path, false);
    planes->AddTexture("texture_baseColor", "rsc/Mesh/White.png", false, true);
    testScene->AddEntity(planes);
    
#pragma region Room
    path = "rsc/Mesh/White.png";
    Cube* floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    testScene->AddEntity(floor);

    float halfSize = 2000.0f;
#pragma endregion

    timer = new DemoEngine_Animations::DemoTimer();
    
    lightManager->directionalLights.push_back({glm::vec3(200.0f, -1.0f, 5.0f), glm::vec3(0.5f)});

    wheelFront = bike->transform->FindChildByName("WheelFront");
    wheelBack = bike->transform->FindChildByName("WheelBack");

    testScene->AddEntity(pCube);
    testScene->AddEntity(shield);
    testScene->AddEntity(mSword);
    testScene->AddEntity(cake);
    testScene->AddEntity(bike);
}

void EarthGame::Update()
{
    MainCamera->SetCameraTarget(pCube->transform->GetGlobalPosition());

    if (this->input->IsKeyPressed(GLFW_KEY_UP)) bike->transform->Translate(vec3{0, 0, -playerSpeed});
    if (this->input->IsKeyPressed(GLFW_KEY_DOWN)) bike->transform->Translate(vec3{0, 0, playerSpeed});
    if (this->input->IsKeyPressed(GLFW_KEY_LEFT)) bike->transform->Translate(vec3{-playerSpeed, 0, 0});
    if (this->input->IsKeyPressed(GLFW_KEY_RIGHT)) bike->transform->Translate(vec3{playerSpeed, 0, 0});
    if (this->input->IsKeyPressed(GLFW_KEY_0)) bike->transform->SetRotationY(bike->transform->GetLocalRotation().y - playerSpeed);
    if (this->input->IsKeyPressed(GLFW_KEY_9)) bike->transform->SetRotationY(bike->transform->GetLocalRotation().y + playerSpeed);
    if (this->input->IsKeyPressed(GLFW_KEY_1)) wheelBack->SetRotationX(wheelBack->GetLocalRotation().x - playerSpeed);
    if (this->input->IsKeyPressed(GLFW_KEY_2)) wheelBack->SetRotationX(wheelBack->GetLocalRotation().x + playerSpeed);

    if (this->input->IsKeyPressed(GLFW_KEY_M))
    {
        wheelFront->SetRotationY(wheelFront->GetLocalRotation().y - playerSpeed);
    }

    if (this->input->IsKeyPressed(GLFW_KEY_N))
    {
        wheelFront->SetRotationY(wheelFront->GetLocalRotation().y + playerSpeed);
    }

    vec3 translation = vec3(0, 0, 0);

    if (input->IsKeyPressed(GLFW_KEY_S))
    {
        translation = vec3(0, 0, 10);
    }
    else if (input->IsKeyPressed(GLFW_KEY_W))
    {
        translation = vec3(0, 0, -10);
    }
    else if (input->IsKeyPressed(GLFW_KEY_A))
    {
        translation = vec3(-10, 0, 0);
    }
    else if (input->IsKeyPressed(GLFW_KEY_D))
    {
        translation = vec3(10, 0, 0);
    }
    else if (input->IsKeyPressed(GLFW_KEY_E))
    {
        translation = vec3(0, 10, 0);
    }
    else if (input->IsKeyPressed(GLFW_KEY_R))
    {
        translation = vec3(0, -10, 0);
    }

    pCube->transform->Translate(translation * 5.0f);

    testScene->Draw(this->MainCamera);
}

void EarthGame::DeInit()
{
    delete idleAnim;
    delete walkAnim;
    delete ballAnim;

    delete pCube;
    delete mSword;
    delete bike;
    delete cake;
    delete shield;
    
    delete floor;
    delete wall1;
    delete wall2;
    delete wall3;
    delete wall4;
    delete Top;

    delete testScene;
}
