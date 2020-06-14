#pragma once
#include <GL/glew.h>
class Texture {
public:
	Texture(const char* filename);
	~Texture();
	void bind();
	void unbind();
	int getImageHeight();
	int getImageWidth();
	int getId();
private:
	int width;
	int height;
	GLuint id;
};

