#include "Camera.h"
#include "MouseInputComponent.h"
#include <iostream>
//#include "Cube.h"
Camera::Camera()
{
	 frustum = new Frustum();
}

void Camera::Update()
{
    GameObject::Update();

	 //Clamp<float>(pitch, -89, 89);
	 cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	 cameraFront.y = sin(glm::radians(pitch)); 
	 cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	 cameraFront = glm::normalize(cameraFront);
	 view = glm::lookAt(position, position + cameraFront, cameraUp);
	 /*if (frustum->InFrustum(position, 0.5))
		  std::cout << "in" << std::endl;
	 else
		  std::cout << "out" << std::endl;*/
	 frustum->Update();
	 frustum->Draw();
	 //cube->Draw();
}
