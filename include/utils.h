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
	// cout<<"Pixel1 size : "<<(unsigned int)(*image->pixels)<<endl;
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

	// cout<<"Pixel size : "<<sizeof((topNight->pixels))/sizeof(char)<<endl;
}

Vec3f colorAtTop(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = (unsigned char)topNight->pixels[3*(1920*y + x)];
			g = (unsigned char)topNight->pixels[3*(1920*y + x) + 1];
			b = (unsigned char)topNight->pixels[3*(1920*y + x) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			r = (unsigned char)topAfternoon->pixels[3*(1024*y + x)];
			g = (unsigned char)topAfternoon->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)topAfternoon->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			r = (unsigned char)topMorning->pixels[3*(1024*y + x)];
			g = (unsigned char)topMorning->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)topMorning->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			r = (unsigned char)topEvening->pixels[3*(512*y + x)];
			g = (unsigned char)topEvening->pixels[3*(512*y + x) + 1];
			b = (unsigned char)topEvening->pixels[3*(512*y + x) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b) + Vec3f(128, 128, 128);
}

Vec3f colorAtRight(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = (unsigned char)rightNight->pixels[3*(1920*y + x)];
			g = (unsigned char)rightNight->pixels[3*(1920*y + x) + 1];
			b = (unsigned char)rightNight->pixels[3*(1920*y + x) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			r = (unsigned char)rightAfternoon->pixels[3*(1024*y + x)];
			g = (unsigned char)rightAfternoon->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)rightAfternoon->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			r = (unsigned char)rightMorning->pixels[3*(1024*y + x)];
			g = (unsigned char)rightMorning->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)rightMorning->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			r = (unsigned char)rightEvening->pixels[3*(512*y + x)];
			g = (unsigned char)rightEvening->pixels[3*(512*y + x) + 1];
			b = (unsigned char)rightEvening->pixels[3*(512*y + x) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b) + Vec3f(128, 128, 128);
}

Vec3f colorAtLeft(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = (unsigned char)leftNight->pixels[3*(1920*y + x)];
			g = (unsigned char)leftNight->pixels[3*(1920*y + x) + 1];
			b = (unsigned char)leftNight->pixels[3*(1920*y + x) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			r = (unsigned char)leftAfternoon->pixels[3*(1024*y + x)];
			g = (unsigned char)leftAfternoon->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)leftAfternoon->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			r = (unsigned char)leftMorning->pixels[3*(1024*y + x)];
			g = (unsigned char)leftMorning->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)leftMorning->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			r = (unsigned char)leftEvening->pixels[3*(512*y + x)];
			g = (unsigned char)leftEvening->pixels[3*(512*y + x) + 1];
			b = (unsigned char)leftEvening->pixels[3*(512*y + x) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b) + Vec3f(128, 128, 128);
}

Vec3f colorAtBack(int x, int y, TimeOfDay tod){
	int r,g,b;
	switch (tod) {
		case TimeOfDay::Night : {
			r = (unsigned char)backNight->pixels[3*(1920*y + x)];
			g = (unsigned char)backNight->pixels[3*(1920*y + x) + 1];
			b = (unsigned char)backNight->pixels[3*(1920*y + x) + 2];
			break;
		}
		case TimeOfDay::Afternoon : {
			r = (unsigned char)backAfternoon->pixels[3*(1024*y + x)];
			g = (unsigned char)backAfternoon->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)backAfternoon->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Morning : {
			r = (unsigned char)backMorning->pixels[3*(1024*y + x)];
			g = (unsigned char)backMorning->pixels[3*(1024*y + x) + 1];
			b = (unsigned char)backMorning->pixels[3*(1024*y + x) + 2];
			break;
		}
		case TimeOfDay::Evening : {
			r = (unsigned char)backEvening->pixels[3*(512*y + x)];
			g = (unsigned char)backEvening->pixels[3*(512*y + x) + 1];
			b = (unsigned char)backEvening->pixels[3*(512*y + x) + 2];
			break;
		}
	}
	return Vec3f((float)r, (float)g, (float)b) + Vec3f(128, 128, 128);
}

Vec3f blendColor(Vec3f color1, float alpha1, Vec3f color2, float alpha2) {
	return (color1*alpha1 + color2*alpha2)/(alpha1 + alpha2);
}
