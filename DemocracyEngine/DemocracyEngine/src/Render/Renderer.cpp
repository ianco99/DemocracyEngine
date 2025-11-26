#include "Renderer.h"

namespace DemoEngine_Renderer
{
    Renderer* Renderer::RendererInstance = nullptr;

    Renderer::Renderer(vec2 windowXY, DemoEngine_Camera::Camera* camera, LightManager* light_manager)
    {
        RendererInstance = this;

        MainCamera = camera;
        lightManager = light_manager;

        GLenum result = glewInit();

        if (result == GLEW_OK)
        {
            std::cout << "Renderer successfully created." << std::endl;
        }
        else
        {
            std::cout << "[RENDERER] Glew initialization error" << std::endl;
        }


        primitiveShader = new Shader("rsc/Shaders/PrimitiveShader.DemoShader");
        textureShader = new Shader("rsc/Shaders/TextureShader.DemoShader");
        lightShader = new Shader("rsc/Shaders/LightsShader.DemoShader");
        modelShader = new Shader("rsc/Shaders/ModelShader.DemoShader");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glEnable(GL_SAMPLE_ALPHA_TO_ONE);

        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        
        float cube_vertices[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
        };
        unsigned int cube_indices[] = {
            0, 1, 1, 2, 2, 3, 3, 0, // Bottom face
            4, 5, 5, 6, 6, 7, 7, 4, // Top face
            0, 4, 1, 5, 2, 6, 3, 7  // Vertical lines
        };

        glGenVertexArrays(1, &m_wireCubeVAO);
        glGenBuffers(1, &m_wireCubeVBO);
        glGenBuffers(1, &m_wireCubeEBO);

        glBindVertexArray(m_wireCubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_wireCubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_wireCubeEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    Renderer::~Renderer()
    {
        delete primitiveShader;
        delete textureShader;

        delete MainCamera;
        delete lightManager;

        glDeleteVertexArrays(1, &m_wireCubeVAO);
        glDeleteBuffers(1, &m_wireCubeVBO);
        glDeleteBuffers(1, &m_wireCubeEBO);

        std::cout << "Deleted renderer." << std::endl;
    }

    void Renderer::Update()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        drawCallsInFrame = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::CreateShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs, int positionsSize,
                               int indexSize)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexSize, indexs, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        std::cout << "Create new Shape." << std::endl;
    }

    void Renderer::CreateSprite(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float* positions, int* indexs,
                                int positionsSize, int indexSize)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, indexs, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // color attribute
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // UV attribute
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void Renderer::BindTexture(const char* textureName, unsigned& textureID, GLint TextureFilter)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilter);

        stbi_set_flip_vertically_on_load(1);

        int width, height, m_BPP;
        unsigned char* localBuffer = textureImporter.GetTexture(textureName, width, height, m_BPP);


        if (m_BPP == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
        else if (m_BPP == 3)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else if (m_BPP == 2)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
        else if (m_BPP == 1)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);


        if (!localBuffer)
        {
            cout << "Failed to load texture" << endl;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        stbi_image_free(localBuffer);
    }

    void Renderer::DestroyShape(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        std::cout << "Delete Shape." << std::endl;
    }

    void Renderer::DrawEntity2D(unsigned int& VAO, mat4x4 model, vec4 color, int sizeIndex) const
    {
        primitiveShader->UseShader();

        mat4 MVP = MainCamera->GetCameraProyection() * MainCamera->GetCameraView() * model;
        primitiveShader->SetMat4("u_MVP", MVP);
        primitiveShader->SetVec4("u_Color", color);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

        primitiveShader->UnuseShader();
    }

    void Renderer::DrawTexture(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, unsigned int& idTexture)
    {
        textureShader->UseShader();

        mat4 MVP = MainCamera->GetCameraProyection() * MainCamera->GetCameraView() * model;
        textureShader->SetMat4("MVP", MVP);
        textureShader->SetFloat("u_AmbientStrength", 1);

        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

        textureShader->UnuseShader();
    }

    void Renderer::DrawEntity3D(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, unsigned int idTexture, Material material)
    {
        lightShader->UseShader();

        lightShader->SetMat4("model", model);
        lightShader->SetMat4("view", MainCamera->GetCameraView());
        lightShader->SetMat4("projection", MainCamera->GetCameraProyection());

        lightShader->SetVec3("material.ambient", material.ambient);
        lightShader->SetVec3("material.diffuse", material.diffuse);
        lightShader->SetVec3("material.specular", material.specular);
        lightShader->SetFloat("material.shininess", material.shininess);

        lightShader->SetVec3("viewPos", MainCamera->GetCameraPosition());

        lightManager->UploadToShader(lightShader);

        lightShader->SetInt("u_Texture", 0);

        if (idTexture != 0)
            glBindTexture(GL_TEXTURE_2D, idTexture);
        else
            glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glActiveTexture(0);

        lightShader->UnuseShader();
    }

    void Renderer::DrawModel(unsigned int VAO, int sizeIndex, vec4 color, mat4x4 model, vector<Texture> textures,
                             Material material)
    {
        modelShader->UseShader();
        drawCallsInFrame++;

        modelShader->SetMat4("model", model);
        modelShader->SetMat4("view", MainCamera->GetCameraView());
        modelShader->SetMat4("projection", MainCamera->GetCameraProyection());

        modelShader->SetVec3("material.ambient", material.ambient);
        modelShader->SetVec3("material.diffuse", material.diffuse);
        modelShader->SetVec3("material.specular", material.specular);
        modelShader->SetFloat("material.shininess", material.shininess);

        modelShader->SetVec3("viewPos", MainCamera->GetCameraPosition());

        lightManager->UploadToShader(modelShader);

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalsNr = 1;
        unsigned int heightNr = 1;
        unsigned int baseColorNr = 1;
        unsigned int metalnessNr = 1;
        unsigned int roughnessNR = 1;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            if (textures[i].id == 0)
            {
                glBindTexture(GL_TEXTURE_2D, -1);
                continue;
            }
            glActiveTexture(GL_TEXTURE0 + i);
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            else if (name == "texture_baseColor")
                number = std::to_string(baseColorNr++);
            else if (name == "texture_normals")
                number = std::to_string(normalsNr++);
            else if (name == "texture_height")
                number = std::to_string(heightNr++);
            else if (name == "texture_metalness")
                number = std::to_string(metalnessNr++);
            else if (name == "texture_roughness")
                number = std::to_string(roughnessNR++);

            modelShader->SetInt("material." + name + number, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);

        modelShader->UnuseShader();
    }

    void Renderer::DrawWireBox(const BoundingBox& box, const mat4& modelMatrix, const vec4& color, float lineWidth)
    {
        primitiveShader->UseShader();
        
        vec3 size = box.max - box.min;
        vec3 center = (box.max + box.min) * 0.5f;
        
        mat4 boxTransform = modelMatrix;
        boxTransform = glm::translate(boxTransform, center);
        boxTransform = glm::scale(boxTransform, size);
        
        mat4 MVP = MainCamera->GetCameraProyection() * MainCamera->GetCameraView() * boxTransform;
        primitiveShader->SetMat4("u_MVP", MVP);
        primitiveShader->SetVec4("u_Color", color);

        glLineWidth(lineWidth);

        glBindVertexArray(m_wireCubeVAO);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        primitiveShader->UnuseShader();
    }

    unsigned int Renderer::GetDrawCalls() const
    {
        return drawCallsInFrame;
    }


    Renderer* Renderer::GetRender()
    {
        return RendererInstance;
    }
}