#include "Window.h"
Window::Window() {
    glfwInit();
    this->window = glfwCreateWindow(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, "Game", NULL, NULL);
    glfwMakeContextCurrent(this->window);

    glewInit();

    glfwSetMouseButtonCallback(this->window, Mouse::MouseButtonCallback);
    glfwSetCursorPosCallback(this->window, Mouse::MousePosCallback);

    glfwSetKeyCallback(this->window, Keyboard::KeyCallback);

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
    glClearColor(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0, 1.0);
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