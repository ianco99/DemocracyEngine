#include "Importer3D.h"
#include "../Entities/Model3D.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glew.h"
#include <../src/Tools/stb_image.h>
#include <iostream>
#include <cstring>

using namespace DemoEngine_Entities;

namespace DemoEngine_Importer
{
    std::vector<Texture> Importer3D::m_loadedTexturesCache;

    ImportedModelData Importer3D::ImportModel(const std::string& path, bool invertTexture, Transform* rootTransform)
    {
        ImportedModelData modelData;
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return modelData;
        }

        aiNode* targetNode = scene->mRootNode;
        if(targetNode->mNumMeshes == 0 && targetNode->mNumChildren == 1)
            targetNode = targetNode->mChildren[0];

        std::string nodeName = targetNode->mName.C_Str();
        if(nodeName.empty() || nodeName == "rootnode" || nodeName == "RootNode" || nodeName.find("Assimp") != std::string::npos)
        {
            size_t lastSlash = path.find_last_of("/\\");
            lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
            size_t lastDot = path.rfind('.');
            modelData.name = (lastDot == std::string::npos || lastDot < lastSlash) ?
                path.substr(lastSlash) :
                path.substr(lastSlash, lastDot - lastSlash);
        }
        else
        {
            modelData.name = nodeName;
            if(rootTransform) rootTransform->SetName(nodeName);
        }

        std::string directory = path.substr(0, path.find_last_of('/'));
        std::cout << "Model loaded: " << path << " | Name: " << modelData.name << " | Meshes: " << scene->mNumMeshes << std::endl;

        if(rootTransform)
            ProcessNode(targetNode, rootTransform, scene, modelData.meshes, directory, invertTexture);

        return modelData;
    }

    void Importer3D::ProcessNode(aiNode* node, Transform* parentTransform, const aiScene* scene,
                                 std::vector<BasicMesh>& outMeshes, const std::string& directory, bool invertTexture)
    {
        Transform* currentTransform = parentTransform;

        if(node->mName.C_Str() != parentTransform->GetName())
        {
            currentTransform = new Transform(parentTransform->GetOwner());
            currentTransform->SetName(node->mName.C_Str());
            currentTransform->SetParent(parentTransform);

            glm::mat4 localMat = glm::transpose(glm::make_mat4(&node->mTransformation.a1));
            glm::vec3 scale, pos, skew;
            glm::quat rot;
            glm::vec4 persp;
            glm::decompose(localMat, scale, rot, pos, skew, persp);

            currentTransform->SetLocalPosition(pos);
            currentTransform->SetLocalRotation(glm::degrees(glm::eulerAngles(rot)));
            currentTransform->SetLocalScale(scale);
        }

        std::string nodeName = node->mName.C_Str();
        if(nodeName.find("bspPlane") != std::string::npos)
        {
            vec3 worldPos = currentTransform->GetGlobalPosition();
            vec3 normal = normalize(currentTransform->GetModelWorldMatrix()[1]); 

            DemoEngine_Renderer::Renderer::GetRender()->MainCamera->AddBSPPlane(worldPos, normal);
            cout << "Plane Found!" << endl;

            if (currentTransform->GetOwner())
            {
                Model3D* model = dynamic_cast<Model3D*>(currentTransform->GetOwner());
                if (model)
                {
                    model->SetAffectedByBspAndFrustum(false);
                }
            }
        }

        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            outMeshes.push_back(ProcessMesh(mesh, scene, directory, invertTexture, currentTransform));
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
            ProcessNode(node->mChildren[i], currentTransform, scene, outMeshes, directory, invertTexture);
    }

    BasicMesh Importer3D::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory,
                                      bool invertTexture, Transform* transform)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v;
            v.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            v.normal = mesh->HasNormals() ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f);
            v.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f);
            v.tangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z) : glm::vec3(0.0f);
            v.bitangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z) : glm::vec3(0.0f);
            vertices.push_back(v);
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }

        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, invertTexture);
            std::vector<Texture> specMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory, invertTexture);
            std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", directory, invertTexture);
            std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height", directory, invertTexture);
            std::vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_baseColor", directory, invertTexture);

            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            textures.insert(textures.end(), specMaps.begin(), specMaps.end());
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
        }

        return BasicMesh(std::move(vertices), std::move(indices), std::move(textures), transform);
    }

    std::vector<Texture> Importer3D::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                          const std::string& typeName, const std::string& directory, bool invertTexture)
    {
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for(const auto& loaded : m_loadedTexturesCache)
            {
                if(std::strcmp(loaded.path.c_str(), str.C_Str()) == 0)
                {
                    textures.push_back(loaded);
                    skip = true;
                    break;
                }
            }
            if(skip) continue;

            std::string texturePath = directory + "/" + str.C_Str();
            unsigned int id = LoadTextureFromFile(texturePath.c_str(), invertTexture);
            Texture tex;
            tex.id = id;
            tex.type = typeName;
            tex.path = str.C_Str();
            textures.push_back(tex);
            m_loadedTexturesCache.push_back(tex);
        }
        return textures;
    }

    unsigned int Importer3D::LoadTextureFromFile(const char* path, bool invertTexture)
    {
        stbi_set_flip_vertically_on_load(invertTexture);
        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if(!data)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            return 0;
        }

        GLenum format = (nrComponents == 1) ? GL_RED : (nrComponents == 3) ? GL_RGB : GL_RGBA;
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        return textureID;
    }
}