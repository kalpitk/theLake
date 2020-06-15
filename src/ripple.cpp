#include <bits/stdc++.h>
#include "../include/ripple.h"
#include "../include/vec3f.h"

#define sq(x) (x)*(x)

using namespace std;
using namespace std::chrono;

Ripple::Ripple(float x, float z, float amp) {
    this->x = x;
    this->z = z;
    this->amp = amp;
    this->startTime = system_clock::now().time_since_epoch() / milliseconds(1);
    this->waveRadius = 2;
}

bool Ripple::operator<(const Ripple& t) const {
    return (this->startTime < t.startTime);

    // Use this to allow multiple ripples at same time
    // Increases CPU Time

    // if(this->startTime != t.startTime)
    // return (this->startTime < t.startTime);
    // if(this->x != t.x) return (this->x < t.x);
    // if(this->z != t.z) return (this->z < t.z);
    // return (this->amp < t.amp);
}

float Ripple::waveDistance() const {
    return timeElapsed()*0.020;
}

inline int Ripple::timeElapsed() const {
    int curTime = system_clock::now().time_since_epoch() / milliseconds(1);
    return curTime - startTime;
}

float Ripple::getAmp(float x, float z) {

    float dist = sqrt(sq(this->x - x) + sq(this->z - z));
    int timeSpent = timeElapsed();

    float waveDist = waveDistance();
    if(dist > waveDist + 2*waveRadius || dist < waveDist - 2*waveRadius) return 0.0f;

    float amplitude = amp*pow(0.9, timeSpent*0.01)*(sqrt(sq(waveRadius) - sq(abs(dist-waveDist) - waveRadius))/waveRadius);

    if(dist < waveDist) amplitude *= -1;

    return amplitude;
}