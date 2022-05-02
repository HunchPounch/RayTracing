#pragma once
using namespace std;
#include "CObject.h"
#include "functions.h"
#include <iostream>

class CFactory {

public:
    virtual Object *Create(vector<float> buffer) = 0;
};
