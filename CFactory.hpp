#pragma once
using namespace std;
#include "CObject.hpp"
#include "functions.hpp"
#include <iostream>

class CFactory {

public:
    virtual Object *Create(vector<float> buffer) = 0;
};
