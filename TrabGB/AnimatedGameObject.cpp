#include "AnimatedGameObject.h"
AnimatedGameObject::AnimatedGameObject(float height, float width, Tile* currentTile) : GameObject(height, width, currentTile, "assets/tree-burning1.png") {
	sprite = new Sprite(4);
	sprite->addFrame(new Texture("assets/tree-burning1.png"));
	sprite->addFrame(new Texture("assets/tree-burning2.png"));
	sprite->addFrame(new Texture("assets/tree-burning3.png"));
	sprite->addFrame(new Texture("assets/tree-burning4.png"));
}

void AnimatedGameObject::draw() {
	milliseconds now = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	if (now - lastFrameTime >= milliseconds(150)) {
		changeCurrentFrame();
		lastFrameTime = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
		);
	}

    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, glm::vec3(((this->currentTile->getPosX() + 12) / (Window::WINDOW_WIDTH / 2)) - 1, ((this->currentTile->getPosY() + 12) / (Window::WINDOW_HEIGHT / 2)) - 1, 0.0f));

    shader->use();
    texture->bind();
    unsigned int transformLocation = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    texture->unbind();
}

void AnimatedGameObject::changeCurrentFrame() {
	this->texture = this->sprite->getCurrentFrame();
}