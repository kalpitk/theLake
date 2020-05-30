#include <bits/stdc++.h>
#include "../include/vec3f.h"

using namespace std;

#define PI 3.1415927

vector<Vec3f> construct_building(float l, float b, float h) {
	vector<Vec3f> t(8);
	t[0] = Vec3f(0,0,0);
	t[1] = Vec3f(b,0,0);
	t[2] = Vec3f(b,h,0);
	t[3] = Vec3f(0,h,0);
	t[4] = Vec3f(0,h,l);
	t[5] = Vec3f(0,0,l);
	t[6] = Vec3f(b,0,l);
	t[7] = Vec3f(b,h,l);
	return t;
}

auto sky_coord = construct_building(500,500,500);
