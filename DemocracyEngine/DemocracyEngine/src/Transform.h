#pragma once
#include "Tools/Export.h"

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace DemoEngine_Entities { class Entity; }

namespace DemoEngine_Entities
{
    using namespace glm;

    class EXPORT Transform
    {
    public:
        explicit Transform(Entity* owner);
        Transform(Entity* owner, Transform* parent);
        Transform(Entity* owner, vec3 pos, vec3 rot, vec3 scale);
        ~Transform();

        // Name
        const std::string& GetName() const;
        void SetName(const std::string& name);

        // Position
        vec3 GetGlobalPosition() const;
        vec3 GetLocalPosition() const;
        void SetLocalPosition(const vec3& newPosition);
        
        void Translate(const vec3& dir);

        // Rotation (Euler angles in degrees)
        vec3 GetLocalRotation() const;
        void SetLocalRotation(const vec3& angles);
        void SetRotationX(float angle);
        void SetRotationY(float angle);
        void SetRotationZ(float angle);

        // Scale
        vec3 GetLocalScale() const;
        void SetLocalScale(const vec3& newScale);

        // Hierarchy
        void SetParent(Transform* newParent);
        Transform* GetParent() const;
        void AddChild(Transform* child);
        void RemoveChild(Transform* child);
        const std::vector<Transform*>& GetChildren() const;
        Transform* FindChildByName(const std::string& name);
        
        // Matrix access
        const mat4& GetModelWorldMatrix() const;
        const mat4& GetModelLocalMatrix() const;

        Entity* GetOwner() const;

    private:
        void UpdateWorldMatrix() const;
        void RecalculateLocalMatrix() const;
        void SetDirty();

        std::string m_name;

        Entity* m_owner;
        Transform* m_parent = nullptr;
        std::vector<Transform*> m_children;
        
        mutable mat4 m_modelLocal;
        mutable mat4 m_modelWorld;

        vec3 m_localPosition;
        vec3 m_localRotation;
        vec3 m_localScale;

        mutable bool m_isDirty = true;
    };
}