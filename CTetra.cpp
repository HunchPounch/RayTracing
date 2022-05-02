#include "CTetra.h"


Tetra::Tetra(vector <float> buffer){
    A.push_back(buffer[0]);
    A.push_back(buffer[1]);
    A.push_back(buffer[2]);
    B.push_back(buffer[3]);
    B.push_back(buffer[4]);
    B.push_back(buffer[5]);
    C.push_back(buffer[6]);
    C.push_back(buffer[7]);
    C.push_back(buffer[8]);
    D.push_back(buffer[9]);
    D.push_back(buffer[10]);
    D.push_back(buffer[11]);

    Cen.push_back((A[0]+B[0]+C[0]+D[0])/4.f);
    Cen.push_back((A[1]+B[1]+C[1]+D[1])/4.f);
    Cen.push_back((A[2]+B[2]+C[2]+D[2])/4.f);
    float xs = D[0]; float ys = D[1]; float zs = D[2];
    float xa = A[0]; float ya = A[1]; float za = A[2];
    float xb = B[0]; float yb = B[1]; float zb = B[2];
    float xc = C[0]; float yc = C[1]; float zc = C[2];

    G.push_back((Det3x3(xs*xs-xa*xa+ys*ys-ya*ya+zs*zs-za*za,ys-ya,zs-za,xs*xs-xb*xb+ys*ys-yb*yb+zs*zs-zb*zb,ys-yb,zs-zb,xs*xs-xc*xc+ys*ys-yc*yc+zs*zs-zc*zc,ys-yc,zs-zc))/(2*(Det3x3(xs-xa,ys-ya,zs-za,xs-xb,ys-yb,zs-zb,xs-xc,ys-yc,zs-zc))));
    G.push_back((Det3x3(xs-xa,xs*xs-xa*xa+ys*ys-ya*ya+zs*zs-za*za,zs-za, xs-xb,xs*xs-xb*xb+ys*ys-yb*yb+zs*zs-zb*zb, zs - zb,xs-xc, xs*xs-xc*xc+ys*ys-yc*yc+zs*zs-zc*zc, zs-zc))/(2*(Det3x3(xs-xa,ys-ya,zs-za,xs-xb,ys-yb,zs-zb,xs-xc,ys-yc,zs-zc))));
    G.push_back((Det3x3(xs-xa,ys-ya, xs*xs-xa*xa+ys*ys-ya*ya+zs*zs-za*za, xs-xb,ys-yb, xs*xs-xb*xb+ys*ys-yb*yb+zs*zs-zb*zb, xs-xc,ys-yc, xs*xs-xc*xc+ys*ys-yc*yc+zs*zs-zc*zc))/(2*(Det3x3(xs-xa,ys-ya,zs-za,xs-xb,ys-yb,zs-zb,xs-xc,ys-yc,zs-zc))));

}

vector<float> Tetra::intersect(const vector<float> &Opoint, const vector<float> &vec){
    float t;
    vector<float> a,b, N;

    if(a.size() == 0){
        if(intersect_triangle(Opoint,vec,A,D,B,t)){
           a = pluss(Opoint,mult(vec,t));
        }
    }

    if(a.size()==0){
        if(intersect_triangle(Opoint,vec,B,D,C,t)){
           a = pluss(Opoint,mult(vec,t));
        }
    }
    if(a.size()!=0){
        if(intersect_triangle(Opoint,vec,B,D,C,t)){
            b = pluss(Opoint,mult(vec,t));
            if(b==a && a.size()!= 0){
                b.pop_back();
                b.pop_back();
                b.pop_back();
                }
        }
    }
    if(a.size()==0){
        if(intersect_triangle(Opoint,vec,A,D,C,t)){
            a = pluss(Opoint,mult(vec,t));
        }
    }
    if(a.size()!=0 && b.size()==0){
        if(intersect_triangle(Opoint,vec,A,D,C,t)){
            b = pluss(Opoint,mult(vec,t));
            if(b==a && a.size()!= 0){
                b.pop_back();
                b.pop_back();
                b.pop_back();
                }
        }
    }

    if(a.size()==0){
        if(intersect_triangle(Opoint,vec,A,B,C,t)){
            a = pluss(Opoint,mult(vec,t));
        }
    }
    if(a.size()!=0 && b.size()==0){
        if(intersect_triangle(Opoint,vec,A,B,C,t)){
           b = pluss(Opoint,mult(vec,t));
            if(b==a && a.size()!= 0){
                b.pop_back();
                b.pop_back();
                b.pop_back();
                }
        }
    }

    if(a.size()==0 && b.size()==0){
        return N;
    }
    if(b.size()==0){
        return a;
    }
    return Near(Opoint, a, b);
}

vector<float> Tetra::normal(const vector<float>& point){
    vector<float> buffer;
    vector<float> check(3);
    if(InPointOnPlane(point, A, B, C)){
            check = minuss(D,point);
            buffer = CrossProduct(minuss(B,A),minuss(C,A));
            if(DotProduct(check,buffer)<0){
                return normalizing(buffer);
            }
            else {
                return normalizing(mult(buffer,-1.f));
            }
    }

    if(InPointOnPlane(point, A, D, C)){
        check = minuss(B,point);
        buffer = CrossProduct(minuss(D,A),minuss(C,A));
        if(DotProduct(check,buffer)<0){
            return normalizing(buffer);
        }
        else {
            return normalizing(mult(buffer,-1.f));
        }
    }

    if(InPointOnPlane(point, A, D, B)){
        check = minuss(C,point);
        buffer = CrossProduct(minuss(B,A),minuss(D,A));
        if(DotProduct(check,buffer)<0){
            return normalizing(buffer);
        }
        else {
            return normalizing(mult(buffer,-1.f));
        }
    }

    if(InPointOnPlane(point, D, B, C)){
        check = minuss(A,point);
        buffer = CrossProduct(minuss(B,D),minuss(C,D));
        if(DotProduct(check,buffer)<0){
            return normalizing(buffer);
        }
        else {
            return normalizing(mult(buffer,-1.f));
        }
    }

    return buffer;
}
