#include "Model3D.h"
#include "../Render/Renderer.h"
#include <iostream>

using namespace DemoEngine_Entities;
using namespace DemoEngine_Importer;
using namespace DemoEngine_Geometry;

namespace DemoEngine_Entities
{
    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale)
        : Entity3D(newPosition, newRotation, newScale)
    {
        _isAffectedByBspAndFrustum = true;
    }

    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture)
        : Entity3D(newPosition, newRotation, newScale)
    {
        _isAffectedByBspAndFrustum = true;
        ImportedModelData data = Importer3D::ImportModel(path, invertTexture, this->transform);
        for (const auto& mesh : data.meshes)
        {
            AddMesh(mesh);
        }
    }

    Model3D::Model3D(const BasicMesh& mesh)
        : Entity3D(vec3(0.0f), vec3(0.0f), vec3(1.0f))
    {
        _isAffectedByBspAndFrustum = true;
        AddMesh(mesh);
    }

    Model3D::~Model3D()
    {
        for (size_t i = 0; i < vaos.size(); ++i)
        {
            glDeleteVertexArrays(1, &vaos[i]);
            glDeleteBuffers(1, &vbos[i]);
            glDeleteBuffers(1, &ebos[i]);
        }
        std::cout << "Delete Model3D" << std::endl;
    }

    void Model3D::AddMesh(const BasicMesh& mesh)
    {
        vertices.push_back(mesh.vertices);
        indices.push_back(mesh.indices);
        meshTransforms.push_back(mesh.transform);
        textures.push_back(mesh.textures);

        ComputeAABBForMesh(vertices.size() - 1);

        unsigned int vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

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

    void Model3D::ComputeAABBForMesh(size_t index)
    {
        BoundingBox box;
        for (Vertex& v : vertices[index])
            box.Expand(v.position);
        meshBoundingBoxes.push_back(box);
    }

    BoundingBox Model3D::ComputeBoundingBoxRecursive(Transform* node)
    {
        BoundingBox box;

        for (int i = 0; i < meshTransforms.size(); ++i)
        {
            Transform* meshTransform = meshTransforms[i];
            Transform* current = meshTransform;
            bool isDescendant = false;
            while (current)
            {
                if (current == node)
                {
                    isDescendant = true;
                    break;
                }
                current = current->GetParent();
            }

            if (isDescendant)
            {
                BoundingBox transformedBox = meshBoundingBoxes[i].Transform(meshTransform->GetModelWorldMatrix());
                box.Expand(transformedBox);
            }
        }

        for (Transform* child : node->GetChildren())
        {
            BoundingBox childBox = ComputeBoundingBoxRecursive(child);
            box.Expand(childBox);
        }

        return box;
    }

    BoundingBox Model3D::GetBoundingBox() const
    {
        vector<BoundingBox> transformedBoxes;
        vector<mat4> transforms;

        for (int i = 0; i < meshBoundingBoxes.size(); ++i)
        {
            transformedBoxes.push_back(meshBoundingBoxes[i]);
            transforms.push_back(meshTransforms[i]->GetModelWorldMatrix());
        }

        return BoundingBox::MergeTransformed(transformedBoxes, transforms);
    }

    bool Model3D::IsVisible(const DemoEngine_Camera::Frustum& frustum) const
    {
        BoundingBox box = GetBoundingBox();
        return frustum.IsBoxVisible(box);
    }

    void Model3D::AddTexture(string type, string path, bool invertTexture, bool clearTexture)
    {
        Texture tex;
        tex.id = Importer3D::LoadTextureFromFile(path.c_str(), invertTexture);
        tex.type = type;
        tex.path = path;

        for (int i = 0; i < textures.size(); ++i)
        {
            if (clearTexture) textures[i].clear();
            textures[i].push_back(tex);
        }
    }

    void Model3D::DrawBoundingBoxesRecursive(Transform* node)
    {
        BoundingBox globalBox = ComputeBoundingBoxRecursive(node);
        Renderer::GetRender()->DrawWireBox(globalBox, mat4(1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), 2.0f);

        for (Transform* child : node->GetChildren())
        {
            DrawBoundingBoxesRecursive(child);
        }
    }

    bool Model3D::IsDescendant(Transform* parent, Transform* child)
    {
        Transform* current = child;
        while (current)
        {
            if (current == parent) return true;
            current = current->GetParent();
        }
        return false;
    }

    void Model3D::DrawRecursive(Transform* node)
    {
        if (!node) return;

        for (int i = 0; i < meshTransforms.size(); ++i)
        {
            if (meshTransforms[i] == node)
            {
                Renderer::GetRender()->DrawModel(
                    vaos[i],
                    static_cast<int>(indices[i].size()),
                    GetColor(),
                    meshTransforms[i]->GetModelWorldMatrix(),
                    textures[i],
                    material
                );
            }
        }

        for (Transform* child : node->GetChildren())
            DrawRecursive(child);
    }

    void Model3D::DrawRecursive(Transform* node, const std::vector<Plane>& bspPlanes, const std::vector<bool>& cameraSides)
    {
        BoundingBox nodeMeshBox = ComputeBoundingBoxRecursive(node);

        for (int i = 0; i < meshTransforms.size(); ++i)
        {
            if (meshTransforms[i] == node)
            {
                break;
            }
        }

        bool isVisibleBSP = true;
        bool isVisibleFrustum = true;

        if (nodeMeshBox.IsValid())
        {
            vec3 corners[8];
            nodeMeshBox.GetCorners(corners);

            for (int i = 0; i < bspPlanes.size(); ++i)
            {
                bool anyCornerOnCameraSide = false;
                for (int c = 0; c < 8; ++c)
                {
                    if (bspPlanes[i].getSide(corners[c]) == cameraSides[i])
                    {
                        anyCornerOnCameraSide = true;
                        break;
                    }
                }
                if (!anyCornerOnCameraSide)
                {
                    isVisibleBSP = false;
                    break;
                }
            }

            const DemoEngine_Camera::Frustum& frustum = Renderer::GetRender()->MainCamera->GetFrustum();
            if (!frustum.IsBoxVisible(nodeMeshBox))
                isVisibleFrustum = false;
        }

        if (_isAffectedByBspAndFrustum && !(isVisibleBSP && isVisibleFrustum)) return;

        for (int i = 0; i < meshTransforms.size(); ++i)
        {
            if (meshTransforms[i] == node)
            {
                Renderer::GetRender()->DrawModel(
                    vaos[i],
                    static_cast<int>(indices[i].size()),
                    GetColor(),
                    meshTransforms[i]->GetModelWorldMatrix(),
                    textures[i],
                    material
                );
            }
        }

        for (Transform* child : node->GetChildren())
            DrawRecursive(child, bspPlanes, cameraSides);
    }


    void Model3D::DrawOccluded(const std::vector<Plane>& bspPlanes, const std::vector<bool>& cameraSides)
    {
        if (isActive)
        {
            DrawRecursive(transform, bspPlanes, cameraSides);
        }

        if (drawWireBox)
        {
            DrawBoundingBoxesRecursive(transform);
        }
    }

    void Model3D::Draw()
    {
        DrawRecursive(transform);
        DrawBoundingBoxesRecursive(transform);
    }
}