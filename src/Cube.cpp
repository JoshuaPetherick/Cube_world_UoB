
#include "Cube.hpp"

 GLuint VertexArrayID;
 GLuint programID;
 GLuint MatrixID;
 GLuint vertexbuffer;
 GLuint colourbuffer;

 static GLfloat g_colour_buffer_data[12*3*3];  // Colours of ground blocks
 static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

void Cube::init()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	programID = LoadShaders( "vertex.vs", "fragment.fs" );

	// One color for each vertex. They were generated randomly.
	for(int i = 0; i < 1*3; i++)
	{ 
		g_colour_buffer_data[3*i+0] = 0.140f;
		g_colour_buffer_data[3*i+1] = 0.059f;
		g_colour_buffer_data[3*i+2] = 0.038f;		
	};

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_colour_buffer_data), g_colour_buffer_data, GL_STATIC_DRAW);
}

void Cube::setupDraw(GLFWwindow* window)
 {
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colours
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
 }

void Cube::draw()
{
	for(float z = 0; z < (2 * 2); z += 2) {
	for(float x = 0; x < (2 * 2); x += 2) {
		drawCube(x, 0.0f, z);
	}
	}

}

void Cube::drawCube(float x, float y, float z)
{
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 12*3); // Draw the triangle ! 3 indices starting at 0 -> 1 triangle
}

void Cube::update( GLFWwindow* window )
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);	

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Cube::close()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
} 

