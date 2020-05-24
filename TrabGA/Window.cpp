#include "Window.h"

const float Window::WINDOW_WIDTH = 512;
const float Window::WINDOW_HEIGHT = 512;


Window::Window() {
    glfwInit();
    this->window = glfwCreateWindow(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, "Game", NULL, NULL);
    glfwMakeContextCurrent(this->window);

    glewInit();

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_ALWAYS);

    glfwSwapInterval(1);
}

bool Window::shouldCloseProgram() {
    return glfwWindowShouldClose(this->window);
}

void Window::onBeforeRender() {
    glClearColor(137.0 / 255.0, 207.0 / 255.0, 240.0 / 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::onAfterRender() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}