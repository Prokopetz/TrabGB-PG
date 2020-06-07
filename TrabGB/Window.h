#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "Keyboard.h"
class Window {
public:
	static const int WINDOW_HEIGHT = 762;
	static const int WINDOW_WIDTH = 1024;
	Window();
	~Window();
	bool shouldCloseProgram();
	void onBeforeRender();
	void onAfterRender();


private:
	GLFWwindow* window;
};

