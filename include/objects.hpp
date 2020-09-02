#include <bits/stdc++.h>
#include "../include/vec3f.hpp"

using namespace std;

vector<Vec3f> constructSky(float l, float b, float h) {
	vector<Vec3f> t = {
		Vec3f(0,0,0),
		Vec3f(b,0,0),
		Vec3f(b,h,0),
		Vec3f(0,h,0),
		Vec3f(0,h,l),
		Vec3f(0,0,l),
		Vec3f(b,0,l),
		Vec3f(b,h,l)
	};
	return t;
}

auto sky_coord = constructSky(500,500,500);
