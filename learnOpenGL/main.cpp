#include <glad/glad.h>	// this is what manages all the function pointers
#include <GLFW/glfw3.h> // Must be included after glad.h 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static void GLAPIENTRY errorOccurredGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);
void triangleFrac(float Ax, float Ay, float Bx, float By, float Cx, float Cy, int depth, unsigned int VBOs[]);


int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	// Error checking
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorOccurredGL, nullptr);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

	// loading textures
	/*
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);


	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// setting texture wrapping/filtering on currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}
	stbi_image_free(data);


	data = stbi_load("images/awesomeface.png", &width, &height, &nrChannels, 0);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// setting texture wrapping/filtering on currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}
	stbi_image_free(data);
	*/


	// SHADERS
	Shader shaders("vertShader.vs", "fragShader.fs");


	unsigned int VAOs[400] = { 0 };
	triangleFrac(-0.5, -0.5, 0.5, -0.5, 0.0, 0.5, 6, VAOs);
	shaders.use();
	//glUniform1i(glGetUniformLocation(shaders.ID, "texture1"), 0); // this is the same as doing it with class as below
	//shaders.setInt("texture2", 1);


	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	*/
		int i = 0;
		while (*(VAOs+i) != 0) 
		{
			shaders.setVec4("color", 1.0, 1.0, 1.0, 1.0);
			if (i % 2 == 0) {
				shaders.setVec4("color", 0.8, 0.3, 0.3, 1.0);
			}
			glBindVertexArray(*VAOs+i);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			i++;
		}

		// show
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void triangleFrac(float Ax, float Ay, float Bx, float By, float Cx, float Cy, int depth, unsigned int VAOs[]) {

	if (depth > 0) {
		float verts[] = {
			Ax, Ay, 0.0f,
			Bx, By, 0.0f,
			Cx, Cy, 0.0f
		};
	
		while (*VAOs != 0) {
			VAOs++;
		}

		//unsigned int VAO;
		glGenVertexArrays(1, VAOs);
		glBindVertexArray(*VAOs);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // telling how to interpret vertex data
		glEnableVertexAttribArray(0);

		float newAx = (Ax + Bx) / 2;
		float newAy = (Ay + By) / 2;
		float newBx = (Bx + Cx) / 2;
		float newBy = (By + Cy) / 2;
		float newCx = (Cx + Ax) / 2;
		float newCy = (Cy + Ay) / 2;

		triangleFrac(newAx, newAy, newBx, newBy, newCx, newCy, depth - 1, VAOs);
		//triangleFrac(newAx, newAy, Bx, By, newCx, newCy, depth - 1, VAOs);
		//triangleFrac(newAx, newAy, newBx, newBy, Cx, Cy, depth - 1, VAOs);

	}
	return;

}

// for if the user changes the size of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

static void GLAPIENTRY errorOccurredGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cout << "[OpenGl error] source: " << source << " type: " << type << " id: " << id
		<< " severity: " << severity << " message: " << message << "\n\n";
	//exit(-1);
}