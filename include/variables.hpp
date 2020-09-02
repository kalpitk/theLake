#pragma once

#include "imageloader.hpp"

// Model Variables
float FSCALE = 100.0f; 
const int X_OFF = 0; 
const int Y_OFF = 0; 
const int Z_OFF = 0;

// Camera Variables
float speed = 0.010f * FSCALE;
float rot_speed = -0.001f;
float yaw  =  3.1*3.1415926530/4.0;
float pitch = -0.67059903716;
float lx,lz,ly;
float camX = 10.696,camY = 300.0,camZ =  20.696;
bool mouseMovedDownState = false;
bool warped = false;
bool fullScreen = false;
bool controls = true;
float swidth=800;
float sheight=600;
float fov=30.0;
float zNear=0.1;
float zFar=20;
int prevMouseX, prevMouseY;
bool cameraMouseMovement = false;

// Object Variables
GLuint ground_texture, 
build1_texture, build2_texture, build3_texture, build4_texture, 
build5_texture, build6_texture, build_top, 
sky_afternoon1, sky_afternoon2, sky_afternoon3, sky_afternoon4,
sky_morning1, sky_morning2, sky_morning3, sky_morning4,
sky_evening1, sky_evening2, sky_evening3, sky_evening4, 
sky_night1, sky_night2, sky_night3, sky_night4; 

// Images
Image *topMorning, *topAfternoon, *topEvening, *topNight,
*backMorning, *backAfternoon, *backEvening, *backNight,
*rightMorning, *rightAfternoon, *rightEvening, *rightNight, 
*leftMorning, *leftAfternoon, *leftEvening, *leftNight;

// Time Variables
enum TimeOfDay {
    Morning,
    Afternoon,
    Evening,
    Night
};
TimeOfDay tod = TimeOfDay::Afternoon;
int timeHours = 15;
