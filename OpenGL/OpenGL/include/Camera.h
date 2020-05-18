#pragma once

#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	//eular angles
	GLfloat yaw;
	GLfloat pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp)); 
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
		{
			this->position = position;
			worldUp = up;
			this->yaw = yaw;
			this->pitch = pitch;
			this->updateCameraVectors();
		}
		Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
		{
			this->position = glm::vec3(posX, posY, posZ);
			worldUp = glm::vec3(upX, upY, upZ);
			this->yaw = yaw;
			this->pitch = pitch;
			this->updateCameraVectors();
		}
		glm::mat4 getViewMatrix()
		{
			return glm::lookAt(this->position, this->position + this->front, this->up);
		}
		void processKeyboard(CameraMovement direction, GLfloat deltaTime)
		{
			GLfloat velocity = movementSpeed * deltaTime;
			if (direction == FORWARD)
				position += front * velocity;
			if (direction == BACKWARD)
				position -= front * velocity;
			if (direction == LEFT)
				position -= right * velocity;
			if (direction == RIGHT)
				position += right * velocity;
		}
		void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constraintPitch = true)
		{
			xOffset *= mouseSensitivity;
			yOffset *= mouseSensitivity;
			yaw += xOffset;
			pitch += yOffset;
			if (constraintPitch)
			{
				if (this->pitch > 89.0f)
					this->pitch = 89.0f;
				if (this->pitch < -89.0f)
					this->pitch = -89.0f;
			}
			this->updateCameraVectors();
		}

		void processMouseScroll(GLfloat yOffset)
		{
			if (this->zoom >= 1.0f && this->zoom <= 45.0f)
				this->zoom -= yOffset;
			if (this->zoom <= 1.0f)
				this->zoom = 1.0f;
			if (this->zoom >= 45.0f)
				this->zoom = 45.0f;
		}

		GLfloat GetZoom()
		{
			return this->zoom;
		}

		glm::vec3 GetPosition()
		{
			return this->position;
		}

		glm::vec3 GetFront()
		{
			return this->front;
		}

};