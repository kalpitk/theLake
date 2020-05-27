#ifndef LAKE_H_INCLUDED
#define LAKE_H_INCLUDED

#include<bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.h"

using namespace std;

class Lake {
	private:
		int w; 
		int l; 
		vector<vector<float>> hs; 
		vector<vector<Vec3f>> normals;
        vector<vector<bool>> isOut;
		bool computedNormals;
        int height;

        // First 2 represent co-ordinates, 3rd defines start time
        vector<vector<Vec3f>> ripples;
	public: 
		Lake(int height);
		~Lake();
		void loadLake();
        void update();
		void compute_normals();
		Vec3f get_normal(int x, int z);
        bool is_outside(int x, int z);
		int width();
		int length();
		void set_height(int x, int z, float y);
		float get_height(int x, int z);
};

#endif