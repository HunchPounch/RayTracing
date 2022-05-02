#pragma once
#include <iostream>
using namespace std;
#include "CObject.h"
#include "CLight.h"
#include <vector>
#include <iterator>
#include <cmath>

vector<float> PointOnPlane(const vector<float>& L, const vector<float>& K,const vector<float>& M, const vector<float>& N,const vector<float>& p, const vector<float>& v);
float Det2x2(float a11,float a12,float a21,float a22);
float Det3x3(float a11,float a12,float a13,float a21,float a22,float a23,float a31,float a32,float a33);
vector<float> Near(const vector<float>& O, const vector<float>& A,const vector<float>& B);
vector<float> InterPoint(const vector<float>& p, const vector<float>& v, const vector<float>& G1, const vector<float>& G2);
bool InRectangle(const vector<float>& Point, const vector<float>& A, const vector<float>& B, const vector<float>& C, const vector<float>& D);
float min4(float a, float b, float c, float d);
float max4(float a, float b, float c, float d);
vector<float> ABC(const vector<float>& L,const vector<float>& K,const vector<float>& M, vector<float> &buffer);
bool InPointOnPlane(const vector<float>& point,const vector<float>& L, const vector<float>& K,const vector<float>& M);
float DotProduct(const vector<float>& a, const vector<float>& b);
vector<float> normalizing(const vector<float> &v);
int Size(stringstream &sss);
bool intersectObject(const vector<float>& Opoint, const vector<float>& vec, vector<Object*> &v, vector<float> &point, vector<float> &n, vector<float> &color);
vector<float> GetRayCol(const vector<float> &Opoint, const vector<float> &vec, vector<Object*> &v, Light &light,const float &limit1, const float &limit2);
vector<float> CrossProduct( const vector<float>& a, const vector<float>& b);
float distance(const vector<float>& a, const vector<float>& b);
vector<float> pluss(const vector<float> &a, const vector<float> &b);
vector<float> minuss(const vector<float>&a, const vector<float>&b);
vector<float> mult(const vector<float>&a, const float &h);
float norm(const vector<float> &a);
bool intersect_triangle(const vector<float> &point, const vector<float>& vec,const  vector<float>& A,const vector<float>& B,const  vector<float>& C, float &t);
vector<float> reflection_vector(const vector<float> &L, const vector<float> &N);
