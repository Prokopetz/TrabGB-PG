#pragma once
#include <GL/glew.h>
class Texture {
public:
	Texture(const char* filename);
	~Texture();
	void bind(int slot);
	void unbind();
private:
	int width;
	int height;
	GLuint id;
};

