#define STB_IMAGE_IMPLEMENTATION

#include <GL/glut.h>
#include <bits/stdc++.h>
#include "../include/variables.h"
#include "../include/vec3f.h"
#include "../include/renderer.h"
#include "../include/terrain.h"
#include "../include/lake.h"
#include "../include/imageloader.h"
#include "../include/utils.h"
#include "../include/objects.h"

extern Terrain* _terrain;
extern Lake* _lake;
float limit=89.0*M_PI/180.0f;
float yview = zNear*FSCALE*tan(fov/2*M_PI/180.0);

float gtx=0.0,gty=0.0,gtz=0.0;

void lakePoint(int x, float y, int z, Vec3f color) {
	// get color here from reflection, apply alpha like this
	if(_lake->is_outside(x, z)) {
		glColor4f(0.0f,0.0f,1.0f,0.0f);
	}
	else {
		Vec3f blendedColor = blendColor(color, 0.8f, Vec3f(100.0, 100.0, 255.0), 0.2f);
		glColor4f(blendedColor[0]/255.0, blendedColor[1]/255.0, blendedColor[2]/255.0, 0.8f);
	}
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  y), FSCALE * (Z_OFF +  z));
}

void timer(int value) {
	_lake->update();
	glutPostRedisplay();
	glutTimerFunc(50,timer,0);
}

void lighting() {
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

float precam_x=cam_x,precam_y=cam_y,precam_z=cam_z;

void collisionDetection(){

	float fac = 3.0f/5;
	float tcam_x = cam_x * fac;
	float tcam_z = cam_z * fac;

	// Collision detection for building
	// for(auto val: building_coord){
	// 	if( cam_y<100 && tcam_x>=val[0] && tcam_x<=val[0]+val[2] && tcam_z>=val[1] && tcam_z<=val[1]+val[3]) {
	// 		cam_x = precam_x;
	// 		cam_y = precam_y;
	// 		cam_z = precam_z;
	// 	}
	// }
	if(cam_y<-25)
		cam_y=-25;
	if(cam_y>500)
		cam_y=500;
	if(cam_x<10)
		cam_x=10;
	if(cam_x>490)
		cam_x=490;
	if(cam_z<10)
		cam_z=10;
	if(cam_z>490)
		cam_z=490;
}

void update_local_vars() {
	if(time_hr > 4 && time_hr <= 11) {
		lighting();
		tod = TimeOfDay::Morning;
	} 
	else if (time_hr > 11 && time_hr <= 15) {
		lighting();
		tod = TimeOfDay::Afternoon;
	} 
	else if (time_hr > 15 && time_hr <= 19) {
		lighting();
		tod = TimeOfDay::Evening;
	} 
	else if ((time_hr > 19 && time_hr<=23) || ((time_hr >=0  && time_hr<=4))){
		lighting();
		tod = TimeOfDay::Night;
	} 
}

string formatTime(){
	string ts;
	if(time_hr<10){
		ts="TIME : 0"+to_string(time_hr)+":00 HRS";
	}
	else{
		ts="TIME : "+to_string(time_hr)+":00 HRS";
	}
	return ts;
}

string ControlStr[]={
	"W: MOVE FORWARD",
	"S: MOVE BACKWARD",
	"A: MOVE LEFT",
	"D: MOVE RIGHT",
	"I: MOVE UP",
	"J: MOVE DOWN",
	"T: INC TIME",
	"SHIFT+T: DEC TIME",
	"C: TOGGLE INSTRUCTIONS",
	"F: TOGGLE FULL SCREEN",
	"ESC: EXIT"
};

void renderText(void *font,string str,float txt_xoff,float txt_yoff,float rc,float gc,float bc){
	txt_xoff=txt_xoff/sheight*yview;
	txt_yoff=txt_yoff/sheight*yview;

	float xoff=cam_x+(zNear+0.0001)*FSCALE*lx+txt_xoff*cos(yaw)-txt_yoff*sin(pitch)*sin(yaw);
	float yoff=cam_y+(zNear+0.0001)*FSCALE*ly+txt_yoff*cos(pitch);
	float zoff=cam_z+(zNear+0.0001)*FSCALE*lz+txt_xoff*sin(yaw)+txt_yoff*sin(pitch)*cos(yaw);
	
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
			cam_x += lx * speed ;
			cam_y += ly * speed ;
			cam_z += lz * speed ;
			break;
		case 's' :
			cam_x -= lx * speed ;
			cam_y -= ly * speed ;
			cam_z -= lz * speed ;
			break;
		case 'a' :
			cam_x += cos(pitch) * sin(yaw - M_PI_2) * speed ;
			cam_z += -cos(pitch) * cos(yaw - M_PI_2) * speed ;
			break;
		case 'd' :
			cam_x += cos(pitch) * sin(yaw + M_PI_2) * speed ;
			cam_z += -cos(pitch) * cos(yaw + M_PI_2) * speed ;
			break;
		case 'i' :
			cam_y += speed ;
			break;
		case 'j': 
			cam_y -= speed ;
			break;
		case 'f':
			if(!full_screen){
				glutFullScreen();
				full_screen=1;
			}
			else{
				glutReshapeWindow(800,600);
				full_screen=0;
			}
			break;
		case 't':
			time_hr=(time_hr+1)%24;
			break;
		case 'T':
			time_hr=(time_hr+23)%24;
			break;
		case 'c':
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

			_lake->addRipple(posX, posZ, 1);
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
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->get_height(x, z)), FSCALE * (Z_OFF +  z));

	normal = _terrain->get_normal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	glTexCoord2f((float)(x)/300,(float)(z+1)/300);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->get_height(x, z + 1)), FSCALE * (Z_OFF +  (z + 1)));
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
			Vec3f normal = _terrain->get_normal(x, z);
			render_points(normal,x,z);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

Vec3f calcReflectRay(Vec3f normal, int x, int y, int z){
	Vec3f cameraPos = Vec3f(cam_x, cam_y, cam_z);
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
	// if(x==174 && z==209){
	// 	cout<<"Dir_x : "<<ray[0]<<" Dir_y : "<<ray[1]<<" Dir_z : "<<ray[2]<<endl;
	// 	cout<<" X : "<<x<<" Y : "<<y<<" Z : "<<z<<endl;
	// 	cout<<"X_act : "<<x_act<<" Y_act : "<<y_act<<" Z_act : "<<z_act<<endl;	
	// }
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

	// x = x/FSCALE;
	// y = y/FSCALE;
	// z = z/FSCALE;
	// cout<<"# x : "<<x<<" z : "<<z<<endl;

	return colorAtTop(100, 100, tod);
}

void render_points_lake(Vec3f normal,int x,int z) {
	glNormal3f(FSCALE * (X_OFF +  normal[0]), FSCALE * (Y_OFF +  normal[1]), FSCALE * (Z_OFF +  normal[2]));
	int y = _lake->get_height(x, z);
	Vec3f colorOff = Vec3f(128.0f,128.0f,128.0f);
	Vec3f reflectRay = calcReflectRay(normal, x, y, z);
	Vec3f color = calcColor(reflectRay, x, y, z);
	lakePoint(x, y, z, color);

	y = _lake->get_height(x, z+1);
	normal = _lake->get_normal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	reflectRay = calcReflectRay(normal, x, y, z+1);
	color = calcColor(reflectRay, x, y, z+1);
	lakePoint(x, y, z+1, color);
}

void render_lake() {

	// For Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int z = 0; z < _lake->length() - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < _lake->width(); x++) {
			Vec3f normal = _lake->get_normal(x, z);
			render_points_lake(normal,x,z);
		}
		glEnd();
	}

	glDisable(GL_BLEND);
}

Vec3f ver[8] = 
{
    {-100.0,-100.0,100.0},
    {-100.0,100.0,100.0},
    {100.0,100.0,100.0},
    {100.0,-100.0,100.0},
    {-100.0,-100.0,-100.0},
    {-100.0,100.0,-100.0},
    {100.0,100.0,-100.0},
    {100.0,-100.0,-100.0},
};

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
			render_sky_helper(sky_night1,sky_night2,sky_night3,sky_night4,sky_night1,sky_night1,Vec3f(-100,-100,-100),sky_coord,4.0f);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	update_local_vars();
	collisionDetection();
	gluLookAt(cam_x,cam_y,cam_z,cam_x+lx,cam_y+ly,cam_z+lz,0.0f,1.0f,0.0f);

	// cout<<cam_x<<' '<<cam_z<<endl;
	// cout<<precam_x<<" "<<precam_z<<"\n\n";
	precam_x=cam_x;
	precam_y=cam_y;
	precam_z=cam_z;
	
	renderText(GLUT_BITMAP_TIMES_ROMAN_24,formatTime(),-swidth+50.0,sheight-80.0,1.0,0.0,0.0);
	
	if(controls){
		for(int i=0;i<11;i++){
			renderText(GLUT_BITMAP_HELVETICA_18,ControlStr[i],-swidth+50.0,sheight-140.0-60.0*i,1.0,1.0,1.0);
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

	ground_texture = loadTx("./resources/terrain_texture.bmp");

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