#include "Menu.h"

Menu::Menu(const char* texturePath) {
    texture = new Texture(texturePath);

    this->shader = new Shader("vertex.shader", "fragment.shader");

    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);

    float vertices[] = {
        // positions         // colors           // texture coords
         -1.0f, 1.0f, 0.0f,   -1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
         1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
         -1.0f, -1.0f, 0.0f,  -1.0f, -1.0f, 1.0f,   0.0f, 0.0f,
         -1.0f, -1.0f, 0.0f,  -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
         1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * 24 * sizeof(float), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shader->use();

    shader->setUniform1i("ourTexture", 0);
}

void Menu::draw() {
    shader->use();
    texture->bind();
    glm::mat4 transform = glm::mat4(1.0f);

    unsigned int transformLocation = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    texture->unbind();
}