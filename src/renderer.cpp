#include <GL/glut.h>
#include <bits/stdc++.h>
#include "../include/variables.hpp"
#include "../include/vec3f.hpp"
#include "../include/renderer.hpp"
#include "../include/terrain.hpp"
#include "../include/lake.hpp"
#include "../include/imageloader.hpp"
#include "../include/utils.hpp"
#include "../include/objects.hpp"

extern Terrain* _terrain;
extern Lake* _lake;

float limit=89.0*M_PI/180.0f;
float yview = zNear*FSCALE*tan(fov/2*M_PI/180.0);

void lakePoint(int x, float y, int z, Vec3f color) {

	if(_lake->isOutside(x, z)) {
		glColor4f(0.0f,0.0f,1.0f,0.0f);
	}
	else {
		// color += Vec3f(128, 128, 128);
		Vec3f blendedColor = blendColor(color, 1.0f, Vec3f(0.0, 0.0, 200.0), 0.0f);
		glColor4f(blendedColor[0]/255.0, blendedColor[1]/255.0, blendedColor[2]/255.0, 0.7f);
	}
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  y), FSCALE * (Z_OFF +  z));
}

void timer(int value) {
	_lake->update();
	glutPostRedisplay();
	glutTimerFunc(50,timer,0);
}

void lighting() {
	switch (tod) {
		case TimeOfDay::Night : {
			GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

			GLfloat lightColor0[] = {0.3f, 0.3f, 0.3f, 0.1f};
			GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

			break;
		}
		case TimeOfDay::Afternoon : {
			float lightOff = (0.2/3.0)*(timeHours - 12);
			GLfloat ambientColor[] = {0.5f-lightOff, 0.5f-lightOff, 0.6f-lightOff, 1.0f};
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

			GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
			GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

			break;
		}
		case TimeOfDay::Morning : {
			float lightOff = (0.5/6.0)*(timeHours - 5);
			GLfloat ambientColor[] = {0.3f+lightOff, 0.3f+lightOff, 0.4f+lightOff, 1.0f};
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

			GLfloat lightColor0[] = {0.4f, 0.4f, 0.5f, 1.0f};
			GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

			break;
		}
		case TimeOfDay::Evening : {
			float lightOff = (0.1/3.0)*(timeHours - 16);
			GLfloat ambientColor[] = {0.3f-lightOff, 0.3f-lightOff, 0.4f-lightOff, 1.0f};
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

			GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
			GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

			break;
		}
	}
}

float precamX=camX,precamY=camY,precamZ=camZ;

void collisionDetection(){

	camX = min(490.0f, camX);
	camY = min(500.0f, camY);
	camZ = min(490.0f, camZ);

	camX = max(10.0f, camX);
	camY = max(-25.0f, camY);
	camZ = max(10.0f, camZ);

}

void update_local_vars() {
	if(timeHours > 4 && timeHours <= 11) {
		lighting();
		tod = TimeOfDay::Morning;
	} 
	else if (timeHours > 11 && timeHours <= 15) {
		lighting();
		tod = TimeOfDay::Afternoon;
	} 
	else if (timeHours > 15 && timeHours <= 19) {
		lighting();
		tod = TimeOfDay::Evening;
	} 
	else if ((timeHours > 19 && timeHours<=23) || ((timeHours >=0  && timeHours<=4))){
		lighting();
		tod = TimeOfDay::Night;
	} 
}

string formatTime(){
	string timeStr = ((timeHours<10) ? "TIME : 0" : "TIME : ") +
						to_string(timeHours)+":00 ";
	return timeStr;
}

string ControlStr[]={
	"LEFT CLICK: Create Ripple",
	"W: Move Forward",
	"S: Move Backward",
	"A: Move Left",
	"D: Move Right",
	"I: Move Up",
	"J: Move Down",
	"R: Dec Time",
	"T: Inc Time",
	"C: Toggle Instructions",
	"F: Toggle Fullscreen",
	"ESC: Exit"
};

void renderText(void *font,string str,float txt_xoff,float txt_yoff,float rc,float gc,float bc){
	txt_xoff=txt_xoff/sheight*yview;
	txt_yoff=txt_yoff/sheight*yview;

	float xoff=camX+(zNear+0.0001)*FSCALE*lx+txt_xoff*cos(yaw)-txt_yoff*sin(pitch)*sin(yaw);
	float yoff=camY+(zNear+0.0001)*FSCALE*ly+txt_yoff*cos(pitch);
	float zoff=camZ+(zNear+0.0001)*FSCALE*lz+txt_xoff*sin(yaw)+txt_yoff*sin(pitch)*cos(yaw);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);

	glColor3f(rc,gc,bc);
	glRasterPos3f(xoff,yoff,zoff);
	for (int i=0; i<str.length(); i++) {
		glutBitmapCharacter(font,str[i]);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
}

void keyboard(unsigned char key,int x,int y){
	switch (key) {
		case 27 :
			exit(0);
		case 'w' :
		case 'W' :
			camX += lx * speed ;
			camY += ly * speed ;
			camZ += lz * speed ;
			break;
		case 's' :
		case 'S' :
			camX -= lx * speed ;
			camY -= ly * speed ;
			camZ -= lz * speed ;
			break;
		case 'a' :
		case 'A' :
			camX += cos(pitch) * sin(yaw - M_PI_2) * speed ;
			camZ += -cos(pitch) * cos(yaw - M_PI_2) * speed ;
			break;
		case 'd' :
		case 'D' :
			camX += cos(pitch) * sin(yaw + M_PI_2) * speed ;
			camZ += -cos(pitch) * cos(yaw + M_PI_2) * speed ;
			break;
		case 'i' :
		case 'I' :
			camY += speed ;
			break;
		case 'j': 
		case 'J' :
			camY -= speed ;
			break;
		case 'f':
		case 'F' :
			if(!fullScreen){
				glutFullScreen();
				fullScreen=1;
			}
			else{
				glutReshapeWindow(800,600);
				fullScreen=0;
			}
			break;
		case 't':
		case 'T' :
			timeHours=(timeHours+1)%24;
			break;
		case 'r':
		case 'R' :
			timeHours=(timeHours+23)%24;
			break;
		case 'c':
		case 'C' :
			controls=!controls;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int mouseX, int mouseY) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cameraMouseMovement = true;
		mouseMovedDownState = false;

		prevMouseX = mouseX;
		prevMouseY = mouseY;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		cameraMouseMovement = false;

		if(!mouseMovedDownState) {
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			GLdouble modelview[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

			GLdouble projection[16];
			glGetDoublev(GL_PROJECTION_MATRIX, projection);

			GLfloat winX, winY, winZ;
			winX = mouseX;
			winY = mouseY;
			winY = (float)viewport[3] - winY;

			glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

			GLdouble posX, posY, posZ;
			gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
			posX = posX / FSCALE - X_OFF;
			posY = posY / FSCALE - Y_OFF;
			posZ = posZ / FSCALE - Z_OFF;

			// Prevent clicks on top skybox
			// from trigerring ripples
			if(posY < 300)
				_lake->addRipple(posX, posZ, 2);
		}
	}
}

void mouseMove(int mouseX, int mouseY) {

	if(!cameraMouseMovement) return;

	if(warped){
		warped=false;
		return;
	}
	pitch += (prevMouseY-mouseY)*rot_speed;
	if(pitch>=limit) pitch=limit;
	else if(pitch<=-limit) pitch= -limit;
	yaw += (mouseX-prevMouseX)*rot_speed;
	lx = cos(pitch)*sin(yaw);
	ly = sin(pitch);
	lz = -cos(pitch)*cos(yaw);
	warped=true;
	glutPostRedisplay();

	prevMouseX = mouseX;
	prevMouseY = mouseY;

	mouseMovedDownState = true;
}

void render_points(Vec3f normal,int x,int z) {
	glNormal3f(FSCALE * (X_OFF +  normal[0]), FSCALE * (Y_OFF +  normal[1]), FSCALE * (Z_OFF +  normal[2]));
	glTexCoord2f((float)(x)/300,(float)(z)/300);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->getHeight(x, z)), FSCALE * (Z_OFF +  z));

	normal = _terrain->getNormal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	glTexCoord2f((float)(x)/300,(float)(z+1)/300);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->getHeight(x, z + 1)), FSCALE * (Z_OFF +  (z + 1)));
}

void render_terrain(GLuint ground_texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground_texture);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glColor3f(1.0f, 1.0f, 1.0f);
	for(int z = 0; z < _terrain->length() - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < _terrain->width(); x++) {
			Vec3f normal = _terrain->getNormal(x, z);
			render_points(normal,x,z);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

Vec3f calcReflectRay(Vec3f normal, int x, int y, int z){
	Vec3f cameraPos = Vec3f(camX, camY, camZ);
	Vec3f currPoint = Vec3f((float)x,(float)y,(float)z);
	Vec3f dir = currPoint - cameraPos;
	normal = normal/normal.magnitude();
	int dotProd = dir[0]*normal[0] + dir[1]*normal[1] + dir[2]*normal[2];
	Vec3f normalVec = normal*dotProd;
	Vec3f reflectRay = dir - (normalVec*2);
	return reflectRay/reflectRay.magnitude();
}

Vec3f calcColor(Vec3f ray, int x, int y, int z){
	float y_act, x_act, z_act;
	float k;
// Intersection with top plane
	y_act = 375*FSCALE;
	k = (float)(y - y_act)/(float)ray[1];
	x_act = (float)x - ray[0]*k;
	z_act = (float)z - ray[2]*k;
	x_act/=FSCALE;
	z_act/=FSCALE;
	y_act/=FSCALE;

	if(x_act >= -125 && x_act <= 375 && z_act >= -125 && z_act <= 375) return colorAtTop(x_act + 125.0, 375 - z_act, tod);

// Intersection with right plane
	x_act = 375*FSCALE;
	k = (float)(x - x_act)/(float)ray[0];
	y_act = y - ray[1]*k;
	z_act = z - ray[2]*k;
	x_act/=FSCALE;
	z_act/=FSCALE;
	y_act/=FSCALE;
	if(y_act >= -125 && y_act <= 375 && z_act >= -125 && z_act <= 375) return colorAtRight(375.0 - z_act, y_act + 125.0, tod);

// Intersection with left plane
	x_act = -125*FSCALE;
	k = (float)(x - x_act)/(float)ray[0];
	y_act = y - ray[1]*k;
	z_act = z - ray[2]*k;
	x_act/=FSCALE;
	z_act/=FSCALE;
	y_act/=FSCALE;
	if(y_act >= -125 && y_act <= 375 && z_act >= -125 && z_act <= 375) return colorAtLeft(z_act + 125.0, y_act + 125.0, tod);

// Intersection with front plane
	z_act = 375*FSCALE;
	k = (float)(z - z_act)/(float)ray[2];
	y_act = y - ray[1]*k;
	x_act = z - ray[0]*k;
	x_act/=FSCALE;
	z_act/=FSCALE;
	y_act/=FSCALE;
	if(y_act >= -125 && y_act <= 375 && x_act >= -125 && x_act <= 375) return colorAtTop(x_act + 125.0, y_act + 125.0, tod);

// Intersection with back plane
	z_act = -125*FSCALE;
	k = (float)(z - z_act)/(float)ray[2];
	y_act = y - ray[1]*k;
	x_act = z - ray[0]*k;
	x_act/=FSCALE;
	z_act/=FSCALE;
	y_act/=FSCALE;
	if(y_act >= -125 && y_act <= 375 && x_act >= -125 && x_act <= 375) return colorAtBack(375.0 - x_act, y_act + 125.0, tod);

	return colorAtTop(100, 100, tod);
}

void render_points_lake(Vec3f normal,int x,int z) {
	glNormal3f(FSCALE * (X_OFF +  normal[0]), FSCALE * (Y_OFF +  normal[1]), FSCALE * (Z_OFF +  normal[2]));
	int y = _lake->getHeight(x, z);
	Vec3f colorOff = Vec3f(128.0f,128.0f,128.0f);
	Vec3f reflectRay = calcReflectRay(normal, x, y, z);
	Vec3f color = calcColor(reflectRay, x, y, z);
	lakePoint(x, y, z, color);

	y = _lake->getHeight(x, z+1);
	normal = _lake->getNormal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	reflectRay = calcReflectRay(normal, x, y, z+1);
	color = calcColor(reflectRay, x, y, z+1);
	lakePoint(x, y, z+1, color);
}

void render_lake() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int z = 0; z < _lake->length() - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < _lake->width(); x++) {
			Vec3f normal = _lake->getNormal(x, z);
			render_points_lake(normal,x,z);
		}
		glEnd();
	}

	glDisable(GL_BLEND);
}

void quad(int a,int b,int c,int d, GLuint building_texture, Vec3f offset,vector<Vec3f> vertices, float scale){
	Vec3f goff = Vec3f(-25,-25,-25);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, building_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

	glTexCoord2f(0.0f, scale);
	glVertex3fv(((vertices[a] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(scale, scale);
    glVertex3fv(((vertices[b] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(scale, 0.0f);
    glVertex3fv(((vertices[c] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(((vertices[d] + offset + goff) * FSCALE).to_float());

    glEnd();
}

void render_sky_helper(GLuint t1,GLuint t2,GLuint t3,GLuint t4,GLuint t5,GLuint t6, Vec3f offset, vector<Vec3f> vertices, float scale) {
	// the coordinates ordering must be clockwise.
    quad(2,7,4,3,t5,offset,vertices, scale); //top
    quad(1,6,5,0,t6,offset,vertices, scale); //bottom
    
	quad(4,7,6,5,t1,offset,vertices, scale); //front
    quad(3,4,5,0,t2,offset,vertices, scale); //right
    quad(0,1,2,3,t3,offset,vertices, scale); //back
    quad(7,2,1,6,t4,offset,vertices, scale); //left
}

void render_sky() {
	switch (tod) {
		case TimeOfDay::Night : {
			render_sky_helper(sky_night1,sky_night2,sky_night3,sky_night4,sky_night1,sky_night1,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
		case TimeOfDay::Afternoon : {
			render_sky_helper(sky_afternoon1,sky_afternoon2,sky_afternoon3,sky_afternoon4,sky_afternoon1,sky_afternoon1,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
		case TimeOfDay::Morning : {
			render_sky_helper(sky_morning1,sky_morning2,sky_morning3,sky_morning4,sky_morning1,sky_morning1,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
		case TimeOfDay::Evening : {
			render_sky_helper(sky_evening1,sky_evening2,sky_evening3,sky_evening4,sky_evening1,sky_evening1,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
	}
}

void drawScene(){
	lx = cos(pitch)*sin(yaw); ly = sin(pitch); lz = -cos(pitch)*cos(yaw);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	update_local_vars();
	collisionDetection();
	gluLookAt(camX,camY,camZ,camX+lx,camY+ly,camZ+lz,0.0f,1.0f,0.0f);

	if(tod==TimeOfDay::Night || tod==TimeOfDay::Evening) renderText(GLUT_BITMAP_9_BY_15,formatTime(),swidth-300.0,sheight-80.0,1.0,1.0,1.0);
	else renderText(GLUT_BITMAP_9_BY_15,formatTime(),swidth-300.0,sheight-80.0,0.0,0.0,0.0);

	if(controls){
		for(int i=0;i<12;i++){
			renderText(GLUT_BITMAP_9_BY_15,ControlStr[i],-swidth+50.0,sheight-80.0-40.0*i,1.0,1.0,1.0);
		}
	}

	float scale = 5.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glScalef(scale, scale, scale);

	render_sky();

	render_terrain(ground_texture);
	render_lake();

	glutSwapBuffers();

}

void handleResize(int w, int h){
    glViewport(0, 0, w, h);
	swidth=w;
	sheight=h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (double)w / (double)h, zNear*FSCALE, zFar * FSCALE);
}

void load_image_resources() {

	ground_texture = loadTx("./resources/ground_terrain.bmp");

	sky_afternoon1 = loadTx("./resources/sky/afternoon/1.bmp");
	sky_afternoon2 = loadTx("./resources/sky/afternoon/2.bmp");
	sky_afternoon3 = loadTx("./resources/sky/afternoon/3.bmp");
	sky_afternoon4 = loadTx("./resources/sky/afternoon/4.bmp");

	sky_evening1 = loadTx("./resources/sky/evening/1.bmp");
	sky_evening2 = loadTx("./resources/sky/evening/2.bmp");
	sky_evening3 = loadTx("./resources/sky/evening/3.bmp");
	sky_evening4 = loadTx("./resources/sky/evening/4.bmp");

	sky_morning1 = loadTx("./resources/sky/morning/1.bmp");
	sky_morning2 = loadTx("./resources/sky/morning/2.bmp");
	sky_morning3 = loadTx("./resources/sky/morning/3.bmp");
	sky_morning4 = loadTx("./resources/sky/morning/4.bmp");

	sky_night1 = loadTx("./resources/sky/night.bmp");
	sky_night2 = sky_night3 = sky_night4 = sky_night1;

	loadImages();
}

void initRendering(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	load_image_resources();
}