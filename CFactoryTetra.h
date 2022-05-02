#pragma once
using namespace std;
#include "CFactory.h"
#include "CTetra.h"
#include <iostream>

class CFactoryTetra : public CFactory {
public:
    virtual Object *Create(vector<float> buffer){return new Tetra(buffer);}
};
