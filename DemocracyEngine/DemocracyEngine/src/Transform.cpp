#include "Transform.h"
#include "Entities/Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>

using namespace DemoEngine_Entities;

Transform::Transform(Entity* owner)
    : m_owner(owner),
      m_localPosition(0.0f),
      m_localRotation(0.0f),
      m_localScale(1.0f),
      m_name("Transform")
{
}

Transform::Transform(Entity* owner, Transform* parent)
    : m_owner(owner),
      m_localPosition(0.0f),
      m_localRotation(0.0f),
      m_localScale(1.0f),
      m_name("Transform")
{
    SetParent(parent);
}

Transform::Transform(Entity* owner, vec3 pos, vec3 rot, vec3 scale)
    : m_owner(owner),
      m_localPosition(pos),
      m_localRotation(rot),
      m_localScale(scale),
      m_name("Transform")
{
}

Transform::~Transform()
{
    SetParent(nullptr);

    auto children_copy = m_children;
    for (Transform* child : children_copy)
    {
        child->SetParent(nullptr);
    }
}

void Transform::UpdateWorldMatrix() const
{
    if (m_isDirty)
    {
        RecalculateLocalMatrix();
        if (m_parent)
        {
            m_modelWorld = m_parent->GetModelWorldMatrix() * m_modelLocal;
        }
        else
        {
            m_modelWorld = m_modelLocal;
        }
        m_isDirty = false;
    }
}

void Transform::RecalculateLocalMatrix() const
{
    mat4 translateMatrix = glm::translate(mat4(1.0f), m_localPosition);

    mat4 rotationX = glm::rotate(mat4(1.0f), glm::radians(m_localRotation.x), vec3(1.0f, 0.0f, 0.0f));
    mat4 rotationY = glm::rotate(mat4(1.0f), glm::radians(m_localRotation.y), vec3(0.0f, 1.0f, 0.0f));
    mat4 rotationZ = glm::rotate(mat4(1.0f), glm::radians(m_localRotation.z), vec3(0.0f, 0.0f, 1.0f));
    mat4 rotationMatrix = rotationY * rotationX * rotationZ;

    mat4 scaleMatrix = glm::scale(mat4(1.0f), m_localScale);

    m_modelLocal = translateMatrix * rotationMatrix * scaleMatrix;
}

void Transform::SetDirty()
{
	if (m_isDirty) return;

	m_isDirty = true;
	for (Transform* child : m_children)
	{
		child->SetDirty();
	}
}

const std::string& Transform::GetName() const
{
    return m_name;
}

void Transform::SetName(const std::string& name)
{
    m_name = name;
}

vec3 Transform::GetGlobalPosition() const
{
    return vec3(GetModelWorldMatrix()[3]);
}

vec3 Transform::GetLocalPosition() const { return m_localPosition; }

void Transform::SetLocalPosition(const vec3& newPosition)
{
    m_localPosition = newPosition;
    SetDirty();
}

void Transform::Translate(const vec3& dir)
{
    m_localPosition += dir;
    SetDirty();
}

vec3 Transform::GetLocalRotation() const { return m_localRotation; }

void Transform::SetLocalRotation(const vec3& angles)
{
    m_localRotation = angles;
    SetDirty();
}

void Transform::SetRotationX(float angle)
{
    m_localRotation.x = angle;
    SetDirty();
}

void Transform::SetRotationY(float angle)
{
    m_localRotation.y = angle;
    SetDirty();
}

void Transform::SetRotationZ(float angle)
{
    m_localRotation.z = angle;
    SetDirty();
}

vec3 Transform::GetLocalScale() const { return m_localScale; }

void Transform::SetLocalScale(const vec3& newScale)
{
    m_localScale = newScale;
    SetDirty();
}

void Transform::SetParent(Transform* newParent)
{
    if (m_parent == newParent) return;

    if (m_parent)
    {
        auto& children = m_parent->m_children;
        auto it = std::find(children.begin(), children.end(), this);
        if (it != children.end())
        {
            children.erase(it);
        }
    }

    m_parent = newParent;

    if (m_parent)
    {
        m_parent->m_children.push_back(this);
    }
    SetDirty();
}

Transform* Transform::GetParent() const { return m_parent; }

void Transform::AddChild(Transform* child)
{
    if (child) child->SetParent(this);
}

void Transform::RemoveChild(Transform* child)
{
    if (child && child->m_parent == this) child->SetParent(nullptr);
}

const std::vector<Transform*>& Transform::GetChildren() const { return m_children; }

Transform* Transform::FindChildByName(const std::string& name)
{
    for (Transform* child : m_children)
    {
        if (child->GetName() == name)
        {
            return child;
        }
        
        Transform* foundInChild = child->FindChildByName(name);
        if (foundInChild)
        {
            return foundInChild;
        }
    }
    return nullptr;
}

const mat4& Transform::GetModelWorldMatrix() const
{
    UpdateWorldMatrix();
    return m_modelWorld;
}

const mat4& Transform::GetModelLocalMatrix() const
{
    if (m_isDirty)
    {
        RecalculateLocalMatrix();
    }
    return m_modelLocal;
}

Entity* Transform::GetOwner() const { return m_owner; }