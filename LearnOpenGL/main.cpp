#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include "Shader.h"
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"

void loadTexture(GLenum unit, const char * image, GLenum format);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window, Camera & cam);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

static Camera camera;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *windows = glfwCreateWindow(1920, 1080, "LearnOpenGL", glfwGetPrimaryMonitor(), nullptr);
	if (windows == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(windows);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1920, 1080);
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(windows, mouse_callback);

	Shader program("source.vs", "source.fs");
	
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera.move(0.0f, 0.0f, 4.0f);

	const glm::mat4 & perspective = glm::perspective(glm::radians(45.0f), 1920.0f / 1080, 0.1f, 100.0f);

	program.use();
	program.setDirLight("dirlight", glm::vec3(0.0f, 0.0f, -1.0),
		glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	program.setFlashLight("flashlight", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

	program.setMat4("projection", perspective);
	program.setFloat("material.shininess", 32.0f);

	Model model("nanosuit/nanosuit.ojbk");

	while (!glfwWindowShouldClose(windows))
	{
		float currentFrame = glfwGetTime();

		processInput(windows, camera);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.setVec3("cameraPos", camera.getPosition());
		program.setMat4("view", camera.getMatrix());
		program.setVec3("flashlight.point.position", camera.getPosition());
		program.setVec3("flashlight.direction", camera.getDirection());

		glm::mat4 mod(1.0f);
		mod = glm::rotate(mod, currentFrame, glm::vec3(0.0f, 1.0f, 0.0f));
		program.setMat4("model", mod);
		model.draw(program);

		glfwSwapBuffers(windows);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Camera & cam)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	static	float lastTime = 0.0f;
	float currentFrame = glfwGetTime();
	float detatime = 0.0f;
	if (lastTime != 0.0f)
		detatime = currentFrame - lastTime;
	lastTime = currentFrame;

	float cameraSpeed = 4.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.move(0.0f, 0.0f, -detatime * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.move(0.0f, 0.0f, detatime * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.move(-detatime * cameraSpeed, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.move(detatime * cameraSpeed, 0.0f, 0.0f);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	float sensitivity = 30.0f;
	static double lastX = 0.0, lastY = 0.0;
	if (lastX != 0.0 || lastY != 0.0)
	{
		double tempX = xpos - lastX;
		double tempY = ypos - lastY;
		camera.rotate(tempX / sensitivity, -tempY / sensitivity);
	}
	lastX = xpos, lastY = ypos;
}
