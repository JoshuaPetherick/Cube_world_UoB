#ifndef CAMERA_HPP
#define CAMERA_HPP

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

void cameraControls(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
