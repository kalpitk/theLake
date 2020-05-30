#pragma once

#include<bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.h"
#include "ripple.h"

using namespace std;

class Lake {
	private:
		int w; 
		int l; 
		vector<vector<float>> hs; 
		vector<vector<Vec3f>> normals;
        vector<vector<bool>> isOut;
        int height;

        set<Ripple> ripples;

	public: 
		Lake(int height);
		~Lake();
		void loadLake();
        void update();
		void compute_normals();
		Vec3f getNormal(int x, int z);
        bool isOutside(int x, int z);
		int width();
		int length();
		void setHeight(int x, int z, float y);
		float getHeight(int x, int z);

		void addRipple(float x, float z, float amp);
};
