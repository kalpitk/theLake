#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include<bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.h"

using namespace std;

class Terrain {
	private:
		int w; 
		int l; 
		vector<vector<float>> hs; 
		vector<vector<Vec3f>> normals;
		bool computedNormals; 
	public: 
		Terrain(int height);
		~Terrain();
		void loadTerrain(int height);
		void compute_normals();
		Vec3f get_normal(int x, int z);
		int width();
		int length();
		void set_height(int x, int z, float y);
		float get_height(int x, int z);
};

#endif