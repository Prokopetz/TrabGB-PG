#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* filename) {
	glGenTextures(1, &this->id);
	int bpp;

	unsigned char* image = stbi_load("assets/texture.jpg", &this->width, &this->height, &bpp, 4);
	
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (image) {
		stbi_image_free(image);
;	}
}

Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

void Texture::bind(int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->id);
}