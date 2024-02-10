#pragma once
#include "CObject.hpp"
#include "functions.hpp"


class Sphere : public Object {

protected:
    vector<float> center;
    float R;

public:
    Sphere(vector<float> buffer);
    Sphere(vector<float> cen, float r);
    vector<float> intersect(const vector<float> &Opoint, const vector<float> &vec);
    vector<float> normal(const vector<float>& point);
    bool BoundSphereInter(const vector<float> &Opoint, const vector<float> &vec){return true;}
};
