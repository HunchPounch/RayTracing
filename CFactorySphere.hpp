#pragma once
using namespace std;
#include "CFactory.hpp"
#include "CSphere.hpp"
#include <iostream>

class CFactorySphere : public CFactory {
public:
    virtual Object *Create(vector <float> buffer){return new Sphere(buffer);}
};
