#pragma once
using namespace std;
#include "CFactory.hpp"
#include "CBox.hpp"
#include <iostream>

class CFactoryBox : public CFactory {
public:
    virtual Object *Create(vector<float> buffer){ return new Box(buffer);}
};
