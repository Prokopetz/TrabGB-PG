#include "GameObject.h"

//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ

GameObject::GameObject(float height, float width, Tile* currentTile) {
    this->height = height;
    this->width = width;
    this->currentTile = currentTile;
    texture = new Texture("assets/Norte.png");
   
    this->shader = new Shader("vertex.shader", "fragment.shader");

    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);

    float widthNormalized = (width / (Window::WINDOW_WIDTH / 2));
    float heightNormalized = (height / (Window::WINDOW_HEIGHT / 2));

    float vertices[] = {
        // positions                                            // colors           // texture coords
         0.0f, heightNormalized, 0.0f,                  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         widthNormalized, heightNormalized, 0.0f,       0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
         0.0f, 0.0f, 0.0f,                              0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         0.0f, 0.0f, 0.0f,                              1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         widthNormalized, heightNormalized, 0.0f,       1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
         widthNormalized, 0.0f, 0.0f,                   1.0f, 1.0f, 0.0f,   1.0f, 0.0f
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

void GameObject::draw() {

    glm::mat4 transform = glm::mat4(1.0f);
    
    transform = glm::translate(transform, glm::vec3(((this->currentTile->getPosX() + 8) / (Window::WINDOW_WIDTH / 2)) - 1, ((this->currentTile->getPosY() + 8) / (Window::WINDOW_HEIGHT / 2)) - 1, 0.0f));

    shader->use();
    texture->bind();
    unsigned int transformLocation = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    texture->unbind();
}


GameObject::~GameObject() {
    std::cout << "Destrutor chamado " << posX << std::endl;
}