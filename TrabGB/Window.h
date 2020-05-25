#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "Keyboard.h"
class Window {
public:
	static const int WINDOW_HEIGHT = 512;
	static const int WINDOW_WIDTH = 512;
	Window();
	~Window();
	bool shouldCloseProgram();
	void onBeforeRender();
	void onAfterRender();


private:
	GLFWwindow* window;
};

