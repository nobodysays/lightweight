#pragma once
#include <list>
#include "Component.h"
#include "helpfile.h"
class GameObject
{
protected:
    std::list<Component*> components;
public:
    glm::vec3 position          = glm::vec3(0);
    glm::vec3 size              = glm::vec3(1);
    glm::vec3 localEulerAngles  = glm::vec3(0);
    inline virtual void Update(const double& deltaTime)
    {
        for (const auto& e : components)
            e->Process(*this, deltaTime);
    }
    virtual void Render() {};
    inline void AddComponent(Component* component)
    {
        components.push_back(component);
    }
};

