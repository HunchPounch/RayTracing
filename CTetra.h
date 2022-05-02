#pragma once
#include "CObject.h"
#include "functions.h"
#include "CSphere.h"

class Tetra : public Object {

protected:
    vector<float> A, B, C, D,G;


public:
    Tetra(vector <float> buffer);
    vector<float> intersect(const vector<float> &Opoint, const vector<float> &vec);
    vector<float> normal(const vector<float>& point);
    bool BoundSphereInter(const vector<float> &Opoint, const vector<float> &vec) {
        Sphere s(Cen,sqrt(distance(G,A)));
        return (s.intersect(Opoint,vec).size() != 0);
    }
};
