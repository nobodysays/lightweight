#include "Camera.h"
#include "MouseInputComponent.h"
#include <iostream>
#include "Game.h"
//#include "Cube.h"
Camera::Camera()
{
	 frustum = new Frustum(fovy, aspect, near, far);
}

void Camera::Update()
{
    GameObject::Update();

	 cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	 cameraFront.y = sin(glm::radians(pitch)); 
	 cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	 cameraFront = glm::normalize(cameraFront);
	 view = glm::lookAt(position, position + cameraFront, cameraUp);


	 glBindBuffer(GL_UNIFORM_BUFFER, Game::GetInstance()->uboMatrices);
	 glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	 glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool Camera::IsSphereInFrustum(const glm::vec3& position, const float& radius)
{
	 glm::vec3 positionInViewSpace = view * glm::vec4(position, 1);
	 return frustum->IsSphereInFrustum(positionInViewSpace, radius);
}
