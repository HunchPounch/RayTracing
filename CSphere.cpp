#include "CSphere.hpp"
#include "functions.hpp"


Sphere::Sphere(vector<float> buffer){
    center.push_back(buffer[0]);
    center.push_back(buffer[1]);
    center.push_back(buffer[2]);
    R = buffer[3];
    Cen=center;
}

Sphere::Sphere(vector<float> cen, float r){
    center = cen;
    R = r;
    Cen=center;
}

vector<float> Sphere::intersect(const vector<float> &Opoint, const vector<float> &vec){

    float x0 = Opoint[0]; float y0 = Opoint[1]; float z0 = Opoint[2];
    float one;
    float two;
    vector<float> null;
    float DD = 4*pow( vec[0]*(x0-center[0])+vec[1]*(y0-center[1])+vec[2]*(z0-center[2]) ,2) - 4*((vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2])*(x0*x0+y0*y0 +z0*z0 + center[0]*center[0]+center[1]*center[1]+center[2]*center[2] -2*x0*center[0]-2*y0*center[1]-2*z0*center[2]-R*R));
    if(DD < 0){
        return null;
    }
    two = (-2*(vec[0]*(Opoint[0]-center[0]) + vec[1]*(Opoint[1]-center[1]) + vec[2]*(Opoint[2]-center[2]) ) - sqrt(DD) )/(2*(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));

    return pluss(Opoint, mult(vec,two));
}

vector<float> Sphere::normal(const vector<float>& point){
    vector<float> n;
    n.push_back((point[0]-center[0]));
    n.push_back((point[1]-center[1]));
    n.push_back((point[2]-center[2]));
    return normalizing(n);
}
