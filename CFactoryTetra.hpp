#pragma once
using namespace std;
#include "CFactory.hpp"
#include "CTetra.hpp"
#include <iostream>

class CFactoryTetra : public CFactory {
public:
    virtual Object *Create(vector<float> buffer){return new Tetra(buffer);}
};
