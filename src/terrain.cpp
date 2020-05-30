#include <bits/stdc++.h>
#include "../include/terrain.h"
#include "../include/vec3f.h"
#include "../include/imageloader.h"


using namespace std;

Terrain::Terrain(int height) {
	loadTerrain(height);
	compute_normals();
}

void Terrain::loadTerrain(int height) {
	this->w =  300;
	this->l =  300;

	hs = vector<vector<float>>(l, vector<float>(w));
	normals = vector<vector<Vec3f>>(l, vector<Vec3f>(w));
	
	for(int y = 0; y < l; y++) {
		for(int x = 0; x < w; x++) {
			float x1 = 0.1*(w/2.0-x);
			float y1 = 0.1*(l/2.0-y);

			// Tweak shape of lake here & in lake class
			float h = min((float)0.0,x1*x1+y1*y1-50)+height;
			this->set_height(x, y, h);
		}
	}
}

Terrain::~Terrain() {
	hs.clear();
	normals.clear();
}

void Terrain::compute_normals() {
	
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
}

Vec3f Terrain::get_normal(int x, int z) {
	return normals[z][x];	
}

int Terrain::width() {
	return w;
}

int Terrain::length() {
	return l;
}

void Terrain::set_height(int x, int z, float y) {
	hs[z][x] = y;
}

float Terrain::get_height(int x, int z) {
	return hs[z][x];	
}