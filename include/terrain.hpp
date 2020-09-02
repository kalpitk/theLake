#pragma once

#include<bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.hpp"

using namespace std;

class Terrain {
	private:
		int w; 
		int l; 
		vector<vector<float>> hs; 
		vector<vector<Vec3f>> normals;

	public: 
		Terrain(int height);
		~Terrain();
		void loadTerrain(int height);
		void compute_normals();
		Vec3f getNormal(int x, int z);
		int width();
		int length();
		void setHeight(int x, int z, float y);
		float getHeight(int x, int z);
};
