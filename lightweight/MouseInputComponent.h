#pragma once
#include "Component.h"
#include <iostream>
class MouseInputComponent : public Component
{
private:
    double prevX=0;
    double prevY=0;
public:
    void Process(GameObject& go) override;
};