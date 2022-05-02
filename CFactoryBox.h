#pragma once
using namespace std;
#include "CFactory.h"
#include "CBox.h"
#include <iostream>

class CFactoryBox : public CFactory {
public:
    virtual Object *Create(vector<float> buffer){ return new Box(buffer);}
};
