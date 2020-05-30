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
	Image* image = loadBMP(str.c_str());
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

Vec3f colorAtTop(float x, float y, TimeOfDay tod){
	int r,g,b;
	int p,q;
	switch (tod) {
		case TimeOfDay::Night : {
			p = (int)(x*(96.0/25.0));
			q = (int)(y*(127.0/50.0));
			r = (unsigned char)topNight->pixels[3*(1920*q + p)];
			g = (unsigned char)topNight->pixels[3*(1920*q + p) + 1];
			b = (unsigned char)topNight->pixels[3*(1920*q + p) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)topAfternoon->pixels[3*(1024*q + p)];
			g = (unsigned char)topAfternoon->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)topAfternoon->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)topMorning->pixels[3*(1024*q + p)];
			g = (unsigned char)topMorning->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)topMorning->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			p = (int)(x*(128.0/125.0));
			q = (int)(y*(128.0/125.0));
			r = (unsigned char)topEvening->pixels[3*(512*q + p)];
			g = (unsigned char)topEvening->pixels[3*(512*q + p) + 1];
			b = (unsigned char)topEvening->pixels[3*(512*q + p) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtRight(float x, float y, TimeOfDay tod){
	int r,g,b;
	int p,q;
	switch (tod) {
		case TimeOfDay::Night : {
			p = (int)(x*(96.0/25.0));
			q = (int)(y*(127.0/50.0));
			r = (unsigned char)rightNight->pixels[3*(1920*q + p)];
			g = (unsigned char)rightNight->pixels[3*(1920*q + p) + 1];
			b = (unsigned char)rightNight->pixels[3*(1920*q + p) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)rightAfternoon->pixels[3*(1024*q + p)];
			g = (unsigned char)rightAfternoon->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)rightAfternoon->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)rightMorning->pixels[3*(1024*q + p)];
			g = (unsigned char)rightMorning->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)rightMorning->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			p = (int)(x*(128.0/125.0));
			q = (int)(y*(128.0/125.0));
			r = (unsigned char)rightEvening->pixels[3*(512*q + p)];
			g = (unsigned char)rightEvening->pixels[3*(512*q + p) + 1];
			b = (unsigned char)rightEvening->pixels[3*(512*q + p) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtLeft(float x, float y, TimeOfDay tod){
	int r,g,b;
	int p,q;
	switch (tod) {
		case TimeOfDay::Night : {
			p = (int)(x*(96.0/25.0));
			q = (int)(y*(127.0/50.0));
			r = (unsigned char)leftNight->pixels[3*(1920*q + p)];
			g = (unsigned char)leftNight->pixels[3*(1920*q + p) + 1];
			b = (unsigned char)leftNight->pixels[3*(1920*q + p) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)leftAfternoon->pixels[3*(1024*q + p)];
			g = (unsigned char)leftAfternoon->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)leftAfternoon->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)leftMorning->pixels[3*(1024*q + p)];
			g = (unsigned char)leftMorning->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)leftMorning->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			p = (int)(x*(128.0/125.0));
			q = (int)(y*(128.0/125.0));
			r = (unsigned char)leftEvening->pixels[3*(512*q + p)];
			g = (unsigned char)leftEvening->pixels[3*(512*q + p) + 1];
			b = (unsigned char)leftEvening->pixels[3*(512*q + p) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f colorAtBack(float x, float y, TimeOfDay tod){
	int r,g,b;
	int p,q;
	switch (tod) {
		case TimeOfDay::Night : {
			p = (int)(x*(96.0/25.0));
			q = (int)(y*(127.0/50.0));
			r = (unsigned char)backNight->pixels[3*(1920*q + p)];
			g = (unsigned char)backNight->pixels[3*(1920*q + p) + 1];
			b = (unsigned char)backNight->pixels[3*(1920*q + p) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)backAfternoon->pixels[3*(1024*q + p)];
			g = (unsigned char)backAfternoon->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)backAfternoon->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			p = (int)(x*(256.0/125.0));
			q = (int)(y*(256.0/125.0));
			r = (unsigned char)backMorning->pixels[3*(1024*q + p)];
			g = (unsigned char)backMorning->pixels[3*(1024*q + p) + 1];
			b = (unsigned char)backMorning->pixels[3*(1024*q + p) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			p = (int)(x*(128.0/125.0));
			q = (int)(y*(128.0/125.0));
			r = (unsigned char)backEvening->pixels[3*(512*q + p)];
			g = (unsigned char)backEvening->pixels[3*(512*q + p) + 1];
			b = (unsigned char)backEvening->pixels[3*(512*q + p) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b);
}

Vec3f blendColor(Vec3f color1, float alpha1, Vec3f color2, float alpha2) {
	return (color1*alpha1 + color2*alpha2)/(alpha1 + alpha2);
}
