#pragma once
#include "helpfile.h"
#include "Shader.h"
#include "GameObject.h"
#include <iostream>
struct Plane
{
    glm::vec3 normal;
    float d;
    Plane(glm::vec3 n, float d) : normal(n), d(d){}
};
class Frustum
{
public:
    Frustum(float fovy, float aspect, float near, float far);
    const float fovy;
    const float aspect;
    const float near;
    const float far;
    bool IsSphereInFrustum(const glm::vec3& p, const float& radius);
private:
    const float alpha = fovy / 2.;
    const float h = 2 * far * tan(alpha);
    const float w = aspect * h;
     
    Plane* planes[6];
};