#include <GL/glut.h>
#include "../include/imageloader.h"
#include "../include/vec3f.h"

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

GLuint loadTx(string str) {
	const char* path = str.c_str();
	Image* image = loadBMP(path);
	GLuint tex = loadTexture(image);
	delete image;
	return tex;
}

// Return the color of reflection
// QUESITON: Take skybox as argument?
Vec3f reflectionColor(Vec3f point, Vec3f direc) {
	
}

Vec3f blendColor(Vec3f color1, float alpha1, Vec3f color2, float alpha2) {
	return (color1*alpha1 + color2*alpha2)/(alpha1 + alpha2);
}
