#include "Model3D.h"

namespace DemoEngine_Entities
{
    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture = false)
        : Entity3D(newPosition, newRotation, newScale)
    {
        auto meshes = Importer3D::ImportModel(path, invertTexture);

        for (const auto& mesh : meshes)
        {
            AddMesh(mesh);
        }
    }

    Model3D::~Model3D()
    {
        std::cout << "Destroy model3d" << std::endl;
        // Optional: cleanup OpenGL buffers
    }

    void Model3D::Draw()
    {
        UpdateTMatrix();

        for (size_t i = 0; i < vaos.size(); ++i)
        {
            Renderer::GetRender()->DrawModel(
                vaos[i],
                static_cast<int>(indices[i].size()),
                getColor(),
                model,
                textures[i],
                material
            );
        }
    }

    void Model3D::AddTexture(std::string type, std::string path, bool invertTexture, bool ClearTexture)
    {
        Texture tex;
        tex.id = Importer3D::LoadTextureFromFile(path.c_str(), invertTexture);
        tex.path = path;
        tex.type = type;

        for (int i = 0; i < textures.size(); ++i)
        {
            if (ClearTexture)
            {
                textures[i].clear();
            }
            textures[i].push_back(tex);
        }
    }

    void Model3D::AddMesh(const BasicMesh& mesh)
    {
        vertices.push_back(mesh.vertices);
        indices.push_back(mesh.indices);
        textures.push_back(mesh.textures);

        unsigned int vao, vbo, ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(3);

        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);

        vaos.push_back(vao);
        vbos.push_back(vbo);
        ebos.push_back(ebo);
    }
}