#pragma once
class Component {
public:
    virtual void Process(class GameObject&, const double& deltaTime)=0;
};