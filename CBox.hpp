#pragma once
#include "CObject.hpp"
#include "functions.hpp"
#include "CSphere.hpp"

class Box : public Object {

protected:
    vector<float> A1, A2, A3, A4, B1, B2, B3, B4;

public:
    Box(vector<float> buffer);
    vector<float> intersect(const vector<float> &Opoint, const vector<float> &vec);
    vector<float> normal(const vector<float>& point);
    bool BoundSphereInter(const vector<float> &Opoint, const vector<float> &vec) {
        Sphere s(Cen,sqrt(distance(Cen,A1)));
        return (s.intersect(Opoint,vec).size() != 0);
    }
};
