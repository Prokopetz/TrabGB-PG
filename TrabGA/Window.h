#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window {
public:
	static const float WINDOW_HEIGHT;
	static const float WINDOW_WIDTH;
	Window();
	~Window();
	bool shouldCloseProgram();
	void onBeforeRender();
	void onAfterRender();


private:
	GLFWwindow* window;
};

