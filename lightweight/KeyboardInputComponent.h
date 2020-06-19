#pragma once
#include "Component.h"
#include "Game.h"
#include "GameObject.h"
class CameraKeyboardInputComponent : public Component
{
    const float speed = 0.01f;
    bool keys[350] = { false };
    void Process(GameObject& go);
};


class UnitsKeyboardInputComponent : public Component
{
    void Process(GameObject& go);
};

