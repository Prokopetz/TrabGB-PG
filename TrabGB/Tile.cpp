#include "Tile.h"
//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ

Tile::Tile(float height, float width, float posX, float posY, glm::vec2 offset, int textureId, float textureWidth, float textureHeight) {
    this->height = height;
    this->width = width;
    this->posX = posX;
    this->posY = posY;
    this->textureId = textureId;

    this->shader = new Shader("vertex.shader", "fragment.shader");
    
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);

    float tileWidth = (width / (Window::WINDOW_WIDTH / 2));
    float tileHeight = (height / (Window::WINDOW_HEIGHT / 2));

    float vertices[] = {
        // positions                                // colors           // texture coords
         0.0f, tileHeight / 2, 0.0f,            1.0f, 0.0f, 0.0f,   0.0f, textureHeight / 2,
         tileWidth / 2, tileHeight, 0.0f,       0.0f, 1.0f, 0.0f,   textureWidth / 2, textureHeight,
         tileWidth / 2, 0.0f, 0.0f,             0.0f, 0.0f, 1.0f,   textureWidth / 2, 0.0f,
         tileWidth, tileHeight / 2, 0.0f,       1.0f, 1.0f, 0.0f,   textureWidth, textureHeight / 2,
         tileWidth / 2, tileHeight, 0.0f,       1.0f, 1.0f, 0.0f,   textureWidth / 2, textureHeight,
         tileWidth / 2, 0.0f, 0.0f,             1.0f, 1.0f, 0.0f,   textureWidth / 2, 0.0f
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

    shader->setUniform1i("ourTexture", this->textureId);

    shader->setUniform2f("offset", offset.x * textureWidth, offset.y * textureHeight);

}

void Tile::draw() {
    
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3((posX / (Window::WINDOW_WIDTH / 2)) - 1, (posY / (Window::WINDOW_HEIGHT / 2)) - 1, 0.0f));

    shader->use();

    unsigned int transformLocation = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


Tile::~Tile() {
    std::cout << "Destrutor chamado " << posX << std::endl;
}

float Tile::getPosX() {
    return this->posX;
}

float Tile::getPosY() {
    return this->posY;
}