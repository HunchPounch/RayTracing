#include "CBox.hpp"


Box::Box(vector<float> buffer){
    vector<float> a(3);
    a[0] = buffer[0];
    a[1] = buffer[1];
    a[2] = buffer[2];
    vector<float> b(3);
    b[0] = buffer[3];
    b[1] = buffer[4];
    b[2] = buffer[5];
    vector<float> tmp(3);
    A1 = a;
    tmp = a;
    tmp[2] += b[2]-a[2];
    A2 = tmp;
    tmp[1] += b[1]-a[1];
    A3 = tmp;
    tmp =a;
    tmp[1] += b[1]-a[1];
    A4 = tmp;
    tmp =a;
    tmp[0] += b[0]-a[0];
    B1 = tmp;
    tmp[2] += b[2]-a[2];
    B2 = tmp;
    tmp[1] += b[1]-a[1];
    B3 = b;
    tmp = a;
    tmp[0] += b[0]-a[0];
    tmp[1] += b[1]-a[1];
    B4 = tmp;

    Cen.push_back((a[0]+b[0])/2);
    Cen.push_back((a[1]+b[1])/2);
    Cen.push_back((a[2]+b[2])/2);
}


vector<float> Box::intersect(const vector<float> &Opoint, const vector<float> &vec){
    vector<float> a,b,null;
    if(a.size() == 0){
        if(InRectangle(PointOnPlane(A1,A2,A3,A4,Opoint,vec),A1,A2,A3,A4)){
            a = PointOnPlane(A1,A2,A3,A4,Opoint,vec);
        }
    }
    //////////////////////////////////////////////////
    if(a.size()==0){
        if(InRectangle(PointOnPlane(A1,A2,B2,B1,Opoint,vec),A1,A2,B2,B1)){
            a = PointOnPlane(A1,A2,B2,B1,Opoint,vec);
        }
    }
    if(a.size()!=0){
        if(InRectangle(PointOnPlane(A1,A2,B2,B1,Opoint,vec),A1,A2,B2,B1)){
            b = PointOnPlane(A1,A2,B2,B1,Opoint,vec);
            if(b==a){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
        }
    }
    ////////////////////////////////////////////////////
    if(a.size()==0){
        if(InRectangle(PointOnPlane(A4,A3,B3,B4,Opoint,vec),A4,A3,B3,B4)){
            a = PointOnPlane(A4,A3,B3,B4,Opoint,vec);
        }
    }
    if(a.size()!=0 && b.size()==0){
        if(InRectangle(PointOnPlane(A4,A3,B3,B4,Opoint,vec),A4,A3,B3,B4)){
            b = PointOnPlane(A4,A3,B3,B4,Opoint,vec);
            if(b==a){
                    b.pop_back();
                    b.pop_back();
                    b.pop_back();
            }
        }
    }

    /////////////////////////////////////////////////////////////
    if(a.size()==0){
        if(InRectangle(PointOnPlane(A2,A3,B3,B2,Opoint,vec),A2,A3,B3,B2)){
            a = PointOnPlane(A2,A3,B3,B2,Opoint,vec);
        }
    }
    if(a.size()!=0 && b.size()==0 ){
        if(InRectangle(PointOnPlane(A2,A3,B3,B2,Opoint,vec),A2,A3,B3,B2)){
            b = PointOnPlane(A2,A3,B3,B2,Opoint,vec);
            if(b==a){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
        }
    }
    ///////////////////////////////////////////////////////////
    if(a.size()==0){
        if(InRectangle(PointOnPlane(B1,B2,B3,B4,Opoint,vec),B1,B2,B3,B4)){
            a = PointOnPlane(B1,B2,B3,B4,Opoint,vec);
        }
    }
    if(a.size()!=0 && b.size() == 0){
        if(InRectangle(PointOnPlane(B1,B2,B3,B4,Opoint,vec),B1,B2,B3,B4)){
            b = PointOnPlane(B1,B2,B3,B4,Opoint,vec);
            if(b==a){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
        }
    }
    ////////////////////////////////////
    if(a.size()==0){
        if(InRectangle(PointOnPlane(A1,A4,B4,B1,Opoint,vec),A1,A4,B4,B1)){
            a = PointOnPlane(A1,A4,B4,B1,Opoint,vec);
        }
    }
    if(a.size()!=0 && b.size()==0){
        if(InRectangle(PointOnPlane(A1,A4,B4,B1,Opoint,vec),A1,A4,B4,B1)){
            b = PointOnPlane(A1,A4,B4,B1,Opoint,vec);
            if(b==a){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
        }
    }
    //////////////////////////////////////////////////////////////
    if(a.size()==0 && b.size()==0){

        return null;
    }
    if(b.size()==0){
        return a;
    }



    return Near(Opoint, a, b);
}


vector<float> Box::normal(const vector<float>& point){
    vector<float> n;
    vector<float> buffer;
    if(point[0]<= A1[0]+ 0.00001f && point[0] >= A1[0]-0.00001f){
        if(InRectangle(point, A1, A2, A3, A4) && n.size()==0){
            ABC(A1,A2,A3,buffer);
            if(buffer[0]>0.f){
                return normalizing(mult(buffer,-1.f));

            }
            else {
                return normalizing(buffer);
            }
        }
    }
    if(point[1]<= A1[1]+ 0.00001f && point[1] >= A1[1]-0.00001f){
        if(InRectangle(point, A1, A2, B2, B1) && n.size()==0){
            ABC(A1,A2,B2,buffer);
            if(buffer[1]>0.f){
               return normalizing(mult(buffer,-1.f));

            }
            else {
                return normalizing(buffer);
            }
        }
    }

    if(point[1]<= A4[1]+ 0.00001f && point[1] >= A4[1]-0.00001f){
        if(InRectangle(point, A4, A3, B3, B4) && n.size()==0){
            ABC(A4,A3,B3,buffer);
            if(buffer[1]<0.f){
                return normalizing(mult(buffer,-1.f));
            }
            else {
                return normalizing(buffer);
            }
        }
    }
    if(point[2]<= A2[2]+ 0.00001f && point[2] >= A2[2]-0.00001f){
        if(InRectangle(point, A2, A3, B3, B2) && n.size()==0){
            ABC(A2,A3,B3,buffer);
            if(buffer[2]<0.f){
                return normalizing(mult(buffer,-1.f));
            }
            else {
                return normalizing(buffer);
            }
        }
    }
    if(point[0]<= B1[0]+ 0.00001f && point[0] >= B1[0]-0.00001f){
        if(InRectangle(point, B1, B2, B3, B4) && n.size()==0){
            ABC(B1,B2,B3,buffer);
            if(buffer[0]<0.f){
                return normalizing(mult(buffer,-1.f));
            }
            else {
                return normalizing(buffer);
            }
        }
    }
    if(point[2]<= A1[2]+ 0.00001f && point[2] >= A1[2]-0.00001f){
        if(InRectangle(point, A1, A4, B4, B1) && n.size()==0){
            ABC(A1,A4,B4,buffer);
            if(buffer[2]>0.f){
                return normalizing(mult(buffer,-1.f));
            }
            else {
                return normalizing(buffer);
            }
        }
    }
    return buffer;
}
