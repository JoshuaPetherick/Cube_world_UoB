#ifndef CUBE_H
#define CUBE_H

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/shader.hpp>

class Cube {
 public:
  void init(); 
  void setupDraw(GLFWwindow* window);
  void draw();
  void update(GLFWwindow* window);
  void close();
 private:
  void drawCube(float x, float y, float z);
};

#endif 
