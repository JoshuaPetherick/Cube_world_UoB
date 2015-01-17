#ifndef CUBE_H
#define CUBE_H

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/shader.hpp>
#include <src/camera.hpp>
#include <src/texture.hpp>

class Cube {
 public:
  void init(); 
  void setupDraw(GLFWwindow* window);
  void drawGround(float xLength, float zLength);
  void drawHouse(float xLength, float zLength);
  void update(GLFWwindow* window);
  void close();
 private:
  void drawCube(float x, float y, float z);

  GLuint VertexArrayID;
  GLuint programID, programID2;
  GLuint MatrixID;
  GLuint vertexbuffer, elementbuffer;
  GLuint colourbuffer, colourbuffer2;
  GLuint uvbuffer;
  GLuint Texture, TextureID;
  GLuint elementbufferlength;
};

 

#endif 
