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

void loadImages(){

	topAfternoon = loadBMP("./resources/sky/afternoon/1.bmp");
	rightAfternoon = loadBMP("./resources/sky/afternoon/2.bmp");
	backAfternoon = loadBMP("./resources/sky/afternoon/3.bmp");
	leftAfternoon = loadBMP("./resources/sky/afternoon/4.bmp");

	topEvening = loadBMP("./resources/sky/evening/1.bmp");
	rightEvening = loadBMP("./resources/sky/evening/2.bmp");
	backEvening = loadBMP("./resources/sky/evening/3.bmp");
	leftEvening = loadBMP("./resources/sky/evening/4.bmp");

	topMorning = loadBMP("./resources/sky/morning/1.bmp");
	rightMorning = loadBMP("./resources/sky/morning/2.bmp");
	backMorning = loadBMP("./resources/sky/morning/3.bmp");
	leftMorning = loadBMP("./resources/sky/morning/4.bmp");

	topNight = loadBMP("./resources/sky/night.bmp");
	rightNight = backNight = leftNight = topNight;
}

Vec3f colorAtTop(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = topNight->pixels[3*(1920*y + x)];
			g = topNight->pixels[3*(1920*y + x) + 1];
			b = topNight->pixels[3*(1920*y + x) + 2];
		}
		case TimeOfDay::Afternoon : {
			r = topAfternoon->pixels[3*(1024*y + x)];
			g = topAfternoon->pixels[3*(1024*y + x) + 1];
			b = topAfternoon->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Morning : {
			r = topMorning->pixels[3*(1024*y + x)];
			g = topMorning->pixels[3*(1024*y + x) + 1];
			b = topMorning->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Evening : {
			r = topEvening->pixels[3*(512*y + x)];
			g = topEvening->pixels[3*(512*y + x) + 1];
			b = topEvening->pixels[3*(512*y + x) + 2];
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtRight(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = rightNight->pixels[3*(1920*y + x)];
			g = rightNight->pixels[3*(1920*y + x) + 1];
			b = rightNight->pixels[3*(1920*y + x) + 2];
		}
		case TimeOfDay::Afternoon : {
			r = rightAfternoon->pixels[3*(1024*y + x)];
			g = rightAfternoon->pixels[3*(1024*y + x) + 1];
			b = rightAfternoon->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Morning : {
			r = rightMorning->pixels[3*(1024*y + x)];
			g = rightMorning->pixels[3*(1024*y + x) + 1];
			b = rightMorning->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Evening : {
			r = rightEvening->pixels[3*(512*y + x)];
			g = rightEvening->pixels[3*(512*y + x) + 1];
			b = rightEvening->pixels[3*(512*y + x) + 2];
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtLeft(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = leftNight->pixels[3*(1920*y + x)];
			g = leftNight->pixels[3*(1920*y + x) + 1];
			b = leftNight->pixels[3*(1920*y + x) + 2];
		}
		case TimeOfDay::Afternoon : {
			r = leftAfternoon->pixels[3*(1024*y + x)];
			g = leftAfternoon->pixels[3*(1024*y + x) + 1];
			b = leftAfternoon->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Morning : {
			r = leftMorning->pixels[3*(1024*y + x)];
			g = leftMorning->pixels[3*(1024*y + x) + 1];
			b = leftMorning->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Evening : {
			r = leftEvening->pixels[3*(512*y + x)];
			g = leftEvening->pixels[3*(512*y + x) + 1];
			b = leftEvening->pixels[3*(512*y + x) + 2];
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtBack(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = backNight->pixels[3*(1920*y + x)];
			g = backNight->pixels[3*(1920*y + x) + 1];
			b = backNight->pixels[3*(1920*y + x) + 2];
		}
		case TimeOfDay::Afternoon : {
			r = backAfternoon->pixels[3*(1024*y + x)];
			g = backAfternoon->pixels[3*(1024*y + x) + 1];
			b = backAfternoon->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Morning : {
			r = backMorning->pixels[3*(1024*y + x)];
			g = backMorning->pixels[3*(1024*y + x) + 1];
			b = backMorning->pixels[3*(1024*y + x) + 2];
		}
		case TimeOfDay::Evening : {
			r = backEvening->pixels[3*(512*y + x)];
			g = backEvening->pixels[3*(512*y + x) + 1];
			b = backEvening->pixels[3*(512*y + x) + 2];
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f blendColor(Vec3f color1, float alpha1, Vec3f color2, float alpha2) {
	return (color1*alpha1 + color2*alpha2)/(alpha1 + alpha2);
}
