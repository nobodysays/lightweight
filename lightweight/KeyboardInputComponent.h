#pragma once
#include "Component.h"
#include "Game.h"
#include "GameObject.h"
class CameraKeyboardInputComponent : public Component
{
    const float speed = 5.f;
    bool keys[350] = { false };
    void Process(GameObject& go, const double& deltaTime);
};


class UnitsKeyboardInputComponent : public Component
{
    void Process(GameObject& go, const double& deltaTime);
};

