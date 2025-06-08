#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shaderClass.h"

#include "SHADERS"
// g++ grind.cpp glad.c -o grinder -I ../include -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl



int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "tester", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glViewport(0, 0, 800, 600);

  float vertices[] =
	{ // positions         // colors
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // top left
		 0.5f, -0.5f, 0.0f,  1.0f, 0.5f, 0.5f, // bottom right
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f  // top right
  };

  unsigned int indices[] =
  {
    0, 1, 3,
    3, 2, 0
  };

  unsigned int vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0); // glVertexAttribPointer(index, attribAmount, type, 
                                                                                 // normalized?, stride (in bytes), offset);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  
  
  Shaders shades;
  shades.shaderCreate(vertexShaderSource, fragShaderSource);

  shades.useProgram(); 

  int colorLocation = glGetUniformLocation(shades.program, "time");

  int transLocation = glGetUniformLocation(shades.program, "rotation"); 

  float time = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
    
    time = glfwGetTime();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
    
    glUniform1f(colorLocation, time);

    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians((float) (time * 100)), glm::vec3(0.0f, 1.0f, 0.0f)); 
    
    glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(rotate));
    

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
	}



	glDeleteProgram(shades.program);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
