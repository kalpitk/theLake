#include<bits/stdc++.h>
#include  "../include/lake.h"
#include  "../include/vec3f.h"
#include  "../include/imageloader.h"


using namespace std;

Lake::Lake(int height) {
    this->height = height;
	this->w =  300;
	this->l =  300;

	hs = vector<vector<float>>(l, vector<float>(w));
	normals = vector<vector<Vec3f>>(l, vector<Vec3f>(w));
    isOut = vector<vector<bool>> (l, vector<bool>(w));

	for(int y = 0; y < l; y++) {
		for(int x = 0; x < w; x++) {
			float x1 = 0.1*(w/2.0-x);
			float y1 = 0.1*(l/2.0-y);

			// Tweak shape of lake here & in terrain class
			float h = x1*x1+y1*y1-50;
            isOut[x][y] = (h>=0);
		}
	}

    update();
}

void Lake::update() {
    computedNormals = false;
	loadLake();
	compute_normals();
}

void Lake::loadLake() {
    for(int y = 0; y < l; y++) {
		for(int x = 0; x < w; x++) {
			set_height(x, y, height);
		}
	}
}

Lake::~Lake() {
	hs.clear();
	normals.clear();
	isOut.clear();
}

void Lake::compute_normals() {
	if (computedNormals) {
		return;
	}
	
	vector<vector<Vec3f>> normals2 = vector<vector<Vec3f>>(l, vector<Vec3f>(w));
	
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum(0.0f, 0.0f, 0.0f);
			
			Vec3f out;
			if (z > 0) {
				out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
			}
			Vec3f in;
			if (z < l - 1) {
				in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
			}
			Vec3f left;
			if (x > 0) {
				left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
			}
			Vec3f right;
			if (x < w - 1) {
				right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
			}
			
			if (x > 0 && z > 0) {
				sum += out.cross(left).normalize();
			}
			if (x > 0 && z < l - 1) {
				sum += left.cross(in).normalize();
			}
			if (x < w - 1 && z < l - 1) {
				sum += in.cross(right).normalize();
			}
			if (x < w - 1 && z > 0) {
				sum += right.cross(out).normalize();
			}
			
			normals2[z][x] = sum;
		}
	}
	
	const float FALLOUT_RATIO = 0.5f;
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum = normals2[z][x];
			
			if (x > 0) {
				sum += normals2[z][x - 1] * FALLOUT_RATIO;
			}
			if (x < w - 1) {
				sum += normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if (z > 0) {
				sum += normals2[z - 1][x] * FALLOUT_RATIO;
			}
			if (z < l - 1) {
				sum += normals2[z + 1][x] * FALLOUT_RATIO;
			}
			
			if (sum.magnitude() == 0) {
				sum = Vec3f(0.0f, 1.0f, 0.0f);
			}
			normals[z][x] = sum;
		}
	}
	
	for(int i = 0; i < l; i++) {
		normals2[i].clear();
	}
	normals2.clear();
	
	computedNormals = true;
}

Vec3f Lake::get_normal(int x, int z) {
	if (!computedNormals) {
		compute_normals();
	}
	return normals[z][x];	
}

bool Lake::is_outside(int x, int z) {
    return isOut[x][z];
}

int Lake::width() {
	return w;
}

int Lake::length() {
	return l;
}

void Lake::set_height(int x, int z, float y) {
	hs[z][x] = y;
	computedNormals = false;
}

float Lake::get_height(int x, int z) {
	return hs[z][x];	
}