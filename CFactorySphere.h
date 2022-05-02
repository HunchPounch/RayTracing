#pragma once
using namespace std;
#include "CFactory.h"
#include "CSphere.h"
#include <iostream>

class CFactorySphere : public CFactory {
public:
    virtual Object *Create(vector <float> buffer){return new Sphere(buffer);}
};
