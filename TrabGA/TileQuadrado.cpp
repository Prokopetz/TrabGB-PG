#include "Tile.h"

Tile::Tile(float height, float width, float posX, float posY) {
    this->height = height;
    this->width = width;
    this->posX = posX;
    this->posY = posY;

    this->shader = new Shader("vertex.shader", "fragment.shader");
    
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);

    float tileWidth = (width / Window::WINDOW_WIDTH);
    float tileHeight = (height / Window::WINDOW_HEIGHT);

    float vertices[] = {
       -tileWidth, -tileWidth,
        tileHeight, -tileHeight,
        tileWidth, tileWidth,

        tileWidth, tileWidth,
        -tileHeight, tileHeight,
        -tileWidth, -tileWidth
    };


    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);



    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tile::draw() {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(((posX + this->width / 2) / (Window::WINDOW_WIDTH / 2)) - 1, ((posY + this->height / 2) / (Window::WINDOW_HEIGHT / 2)) - 1, 0.0f));

    shader->use();

    unsigned int transformLocation = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Tile::~Tile() {
    std::cout << "Destrutor chamado " << posX << std::endl;
}