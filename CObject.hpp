#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

class Object{
protected:
    vector<float> StartColor;
    vector<float> Cen;
    float DistToCam;

public:
    virtual ~Object(){}
    virtual vector<float> intersect(const vector<float> &Opoint, const vector<float> &vec) = 0;
    virtual vector<float> normal(const vector<float>& point) = 0;
    virtual bool BoundSphereInter(const vector<float> &Opoint, const vector<float> &vec) = 0;

    vector<float> GetColor(){return StartColor;}
    void SetColor(vector<float> col){StartColor = col;}
    void SetDistToCam(const vector<float> &cam){DistToCam = (Cen[0]-cam[0])*(Cen[0]-cam[0])+ (Cen[1]-cam[1])*(Cen[1]-cam[1]) +(Cen[2]-cam[2])*(Cen[2]-cam[2]);}
    float GetDistToCam(){return DistToCam; }
    bool operator <(Object& b) const { return (this->DistToCam < b.GetDistToCam());}

};
