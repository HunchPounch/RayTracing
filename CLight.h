#pragma once
#include <iostream>
#include "functions.h"
using namespace std;
#include <vector>

class Light {
private:
    vector<float> point;
public:
    Light(){}
    Light(const vector<float> &p){point = p;}
    vector<float> LRay(const vector<float> &pp){
        vector<float> Ray;
        Ray.push_back(point[0]-pp[0]);Ray.push_back(point[1]-pp[1]);Ray.push_back(point[2]-pp[2]);
        return Ray;
    }
    void push_b(const float &b){point.push_back(b);}

};
