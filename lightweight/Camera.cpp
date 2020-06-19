#include "Camera.h"
#include "MouseInputComponent.h"
//#include "Cube.h"
Camera::Camera()
{
	 //cube = new Cube();
	 //cube->position = { 1, 0, -3 };
}

void Camera::Update()
{
    GameObject::Update();

	 //Clamp<float>(pitch, -89, 89);
	 cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	 cameraFront.y = sin(glm::radians(pitch)); 
	 cameraFront.z = -cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	 cameraFront = glm::normalize(cameraFront);
	 view = glm::lookAt(position, position + cameraFront, cameraUp);

	 //cube->Draw();
}
