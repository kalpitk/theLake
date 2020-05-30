#pragma once

#include <bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.h"

using namespace std;

class Ripple {
	private:
		float x, z;
        float amp;
        long long startTime;
        float waveRadius;

    public:
        Ripple(float x, float z, float amp);
        bool operator<(const Ripple &t) const;

        float getAmp(float x, float z);
        float waveDistance() const;
        int timeElapsed() const;
};
