#pragma once
using namespace std;

template<typename T>
bool is_similar(T left, T right, T epsilon = 0.0001){

    return abs(left - right) <= epsilon;
}
