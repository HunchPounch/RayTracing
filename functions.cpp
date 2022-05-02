#include "functions.h"
#include "template.h"


float Det2x2(float a11,float a12,float a21,float a22){

    return a11*a22-a12*a21;
}

float Det3x3(float a11,float a12,float a13,float a21,float a22,float a23,float a31,float a32,float a33){

    return a11*Det2x2(a22,a23,a32,a33) - a12*Det2x2(a21, a23, a31, a33) + a13*Det2x2(a21,a22,a31,a32);
}

vector<float> PointOnPlane(const vector<float>& L, const vector<float>& K, const vector<float>& M, const vector<float>& N, const vector<float>& p, const vector<float>& v){
    float L1=L[0]; float L2=L[1]; float L3=L[2]; float K1=K[0]; float K2=K[1] ; float K3=K[2]; float M1=M[0]; float M2=M[1]; float M3=M[2];
    float x0=p[0]; float y0=p[1]; float z0=p[2]; float alpha=v[0]; float beta=v[1]; float gamma=v[2];
    float A = Det2x2(K2-L2,K3-L3,M2-L2,M3-L3);
    float B = -Det2x2(K1-L1,K3-L3,M1-L1,M3-L3);
    float C = Det2x2(K1-L1,K2-L2,M1-L1,M2-L2);
    float D = -L1*A - L2*B - L3*C;

    vector<float> a, b, null;
    if(N.size() != 0){
        if(is_similar(A*alpha+B*beta+C*gamma, 0.0f)){

            if(is_similar(-D-A*x0-B*y0-C*z0,0.0f)){
                if(InterPoint(p,v,L,K).size() != 0){
                    a = InterPoint(p,v,L,K);
                }
                if(a.size() == 0){
                    a = InterPoint(p,v,K,M);
                }
                if(a.size() != 0){
                    b = InterPoint(p,v,K,M);
                    if(b==a && a.size()!= 0){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
                }
                if(a.size() == 0){
                    a = InterPoint(p,v,M,N);
                }
                if(a.size() != 0 && b.size() == 0){
                    b = InterPoint(p,v,M,N);
                    if(b==a && a.size()!= 0){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
                }
                if(a.size() == 0){
                    a = InterPoint(p,v,L,N);
                }
                if(a.size() != 0 && b.size() == 0){
                    b = InterPoint(p,v,L,N);
                    if(b==a && a.size()!= 0){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
                }
                if(b.size() == 0){
                    return a;
                }
                return Near(p,a,b);
            }
            else {
                return null;
            }
        }
    }
    else {
        if(is_similar(A*alpha+B*beta+C*gamma, 0.0f)){
            if(is_similar(-D-A*x0-B*y0-C*z0,0.0f)){
                if(InterPoint(p,v,L,K).size() != 0){
                    a = InterPoint(p,v,L,K);
                }

                if(a.size() == 0){
                    a = InterPoint(p,v,K,M);
                }
                if(a.size() != 0){
                    b = InterPoint(p,v,K,M);
                    if(b==a && a.size()!= 0){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
                }

                if(a.size() == 0){
                    a = InterPoint(p,v,L,M);
                }
                if(a.size() != 0 && b.size() ==0){
                    b = InterPoint(p,v,L,M);
                    if(b==a && a.size()!= 0){
                        b.pop_back();
                        b.pop_back();
                        b.pop_back();
                    }
                }

                if(b.size() == 0){
                    return a;
                }
                return Near(p,a,b);
            }
            else {
                return null;
            }
        }
    }

        null.push_back(x0 +  alpha*((-D-A*x0-B*y0-C*z0)/(A*alpha+B*beta+C*gamma)) );
        null.push_back(y0 +  beta*((-D-A*x0-B*y0-C*z0)/(A*alpha+B*beta+C*gamma)) );
        null.push_back(z0 +  gamma*((-D-A*x0-B*y0-C*z0)/(A*alpha+B*beta+C*gamma)) );

        return null;
}

float min4(float a, float b, float c, float d) {
    return min(min(a, b), min(c, d));
}
float max4(float a, float b, float c, float d) {
    return max(max(a, b), max(c, d));
}


vector<float> Near(const vector<float>& O, const vector<float>& A, const vector<float>& B){
    if(B.size()==0){
        return A;
    }
    float check =  min(distance(O,A), distance(O,B));
    if(is_similar(check,distance(O,A))) return A;
    if(is_similar(check,distance(O,B))) return B;
    return A;
}


float distance(const vector<float>& O, const vector<float>& A){
    return (A[0]-O[0])*(A[0]-O[0]) + (A[1]-O[1])*(A[1]-O[1]) + (A[2]-O[2])*(A[2]-O[2]);
}

vector<float> InterPoint(const vector<float>& p, const vector<float>& v, const vector<float>& G1, const vector<float>& G2){
    float x0=p[0]; float y0=p[1]; float z0=p[2]; float alpha=v[0]; float beta=v[1]; float gamma=v[2];
    float alpha1=G2[0]-G1[0]; float beta1=G2[1]-G1[1]; float gamma1=G2[2]-G1[2];
    float x1=G1[0]; float y1=G1[1]; float z1=G1[2];
    vector <float> null;

    if(is_similar(beta*alpha1-beta1*alpha, 0.0f)){
        if(is_similar(x0*beta*alpha1-x1*beta1*alpha-y0*alpha*alpha1+y1*alpha*alpha, 0.0f)){
            return Near(p, G1, G2);
        }
        else {
            return null;
        }
    }
    if(is_similar(alpha*beta1-alpha1*beta, 0.0f)){
        if(is_similar(y0*alpha*beta1-y1*alpha1*beta-x0*beta*beta1+x1*beta*beta1, 0.0f)){
            return Near(p, G1, G2);
        }
        else{
            return null;
        }
    }
    if(is_similar(beta*gamma1-gamma*beta1,0.0f)){

        if(is_similar(z0*beta*gamma1-z1*beta1*gamma-y0*gamma1*gamma+y1*gamma*gamma1, 0.0f)){
            return Near(p, G1, G2);
        }
        else {
            return null;
        }
    }
    null.push_back( (x0*beta*alpha1-x1*beta1*alpha-y0*alpha*alpha1+y1*alpha*alpha)/(beta*alpha1-beta1*alpha) );
    null.push_back( (y0*alpha*beta1-y1*alpha1*beta-x0*beta*beta1+x1*beta*beta1)/(alpha*beta1-alpha1*beta) );
    null.push_back( (z0*beta*gamma1-z1*beta1*gamma-y0*gamma1*gamma+y1*gamma*gamma1)/(beta*gamma1-gamma*beta1) );

    return null;
}

bool InRectangle(const vector<float>& Point,const vector<float>& A,const vector<float>& B, const vector<float>& C, const vector<float>& D){
    if(Point.size() == 0){
        return false;
    }
    float miny;
    float minz;
    float minx;
    float maxx;
    float maxy;
    float maxz;
    if(A[0]==B[0]&& B[0]==C[0]&&C[0]==D[0]){
     miny = min4( A[1],B[1],C[1],D[1] );
     minz = min4( A[2],B[2],C[2],D[2] );
     maxy = max4( A[1],B[1],C[1],D[1] );
     maxz = max4( A[2],B[2],C[2],D[2] );
        if(miny <= Point[1] && Point[1] <= maxy && minz <= Point[2] && Point[2] <= maxz){
            return true;
        }
        else {
            return false;
        }
    }

    if(A[1]==B[1]&& B[1]==C[1]&&C[1]==D[1]){
     minx = min4( A[0],B[0],C[0],D[0] );
     minz = min4( A[2],B[2],C[2],D[2] );
     maxx = max4( A[0],B[0],C[0],D[0] );
     maxz = max4( A[2],B[2],C[2],D[2] );
        if(minx <= Point[0] && Point[0] <= maxx && minz <= Point[2] && Point[2] <= maxz){
            return true;
        }
        else {
            return false;
        }
    }

    if(A[2]==B[2]&& B[2]==C[2]&&C[2]==D[2]){
     minx = min4( A[0],B[0],C[0],D[0] );
     miny = min4( A[1],B[1],C[1],D[1] );
     maxx = max4( A[0],B[0],C[0],D[0] );
     maxy = max4( A[1],B[1],C[1],D[1] );
        if(minx <= Point[0] && Point[0] <= maxx && miny <= Point[1] && Point[1] <= maxy){
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

bool intersect_triangle(const vector<float> &point, const vector<float>& vec,const  vector<float>& A,const vector<float>& B,const  vector<float>& C, float &t){
   float u,v;
   vector<float> E1 = minuss(B,A);
   vector<float> E2 = minuss(C,A);
   vector<float> N = CrossProduct(E1,E2);
   float det = -DotProduct(vec, N);
   float invdet = 1.0f/det;
   vector<float> AO  = minuss(point,A);
   vector<float> DAO = CrossProduct(AO, vec);
   u =  DotProduct(E2,DAO)*invdet;
   v = -DotProduct(E1,DAO)*invdet;
   t =  DotProduct(AO,N)*invdet;

   return (fabs(det) >= 1e-6 && t >= 0.0f && u >= 0.0f && v >= 0.0f && (u+v) <= 1.0f);
}


vector<float> ABC(const vector<float>& L, const vector<float>& K,const vector<float>& M, vector<float> &buffer){
    float L1=L[0]; float L2=L[1]; float L3=L[2]; float K1=K[0]; float K2=K[1] ; float K3=K[2]; float M1=M[0]; float M2=M[1]; float M3=M[2];
    float A = Det2x2(K2-L2,K3-L3,M2-L2,M3-L3);
    float B = -Det2x2(K1-L1,K3-L3,M1-L1,M3-L3);
    float C = Det2x2(K1-L1,K2-L2,M1-L1,M2-L2);
    buffer.push_back(A);
    buffer.push_back(B);
    buffer.push_back(C);
    return buffer;
}

bool InPointOnPlane(const vector<float>& point,const vector<float>& L, const vector<float>& K,const vector<float>& M){

    if(is_similar(DotProduct(minuss(L,point),CrossProduct(minuss(K,L),minuss(M,L))),0.f)){
        return true;
    }
    else {
        return false;
    }
    return true;

}

float DotProduct(const vector<float>& a, const vector<float>& b){

    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

vector<float> normalizing(const vector<float> &v){
    vector<float> newv;

    newv.push_back( v[0]/(sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])));
    newv.push_back( v[1]/(sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])));
    newv.push_back( v[2]/(sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])));

    return newv;
}

int Size(stringstream &sss){
    int count1 = 0;
    string word;
    while (sss >> word)
            count1++;
    return count1;
}


bool intersectObject(const vector<float>& Opoint, const vector<float>&  vec, vector<Object*> &v, vector<float> &point, vector<float> &n, vector<float> &color){
    vector<float> buf;
    for(vector<Object*>::iterator it = v.begin(); it!=v.end(); ++it){

        if(point.size()==0){
            if((*it)->BoundSphereInter(Opoint,vec)){
                    point = (*it)->intersect(Opoint, vec);
            }
            if(point.size()!=0){
                n = (*it)->normal(point);
                color = (*it)->GetColor();
            }
        }
        else {
             if((*it)->BoundSphereInter(Opoint,vec)){
                buf = (*it)->intersect(Opoint, vec);
                point = Near(Opoint, point, buf);
                if(buf.size()!=0){
                    if(is_similar(point[0],buf[0]) && is_similar(point[1],buf[1]) && is_similar(point[2],buf[2])){
                        n = (*it)->normal(point);
                        color = (*it)->GetColor();
                    }
                }
             }
        }
    }
    if(point.size()==0){
        return false;
    }
    else {
        return true;
    }
    return false;
}


vector<float> GetRayCol(const vector<float> &Opoint, const vector<float> &vec, vector<Object*> &v, Light &light,const float &limit1, const float &limit2){
    vector<float> point, n(3), color;
    vector<float> answer(3);
    vector<float> backgroung;
    float spec;
    float specularStrength = 0.3f;
    float diffuseStrength = 0.85f;
    float ambientStrength = 0.1f;
    float gloss_factor = 6.f;
    float lightColor = 1.f;
    float ambient = ambientStrength*lightColor;
    backgroung.push_back(0);
    backgroung.push_back(0);
    backgroung.push_back(0);

    if(!(intersectObject(Opoint,vec,v,point,n,color))){

        return backgroung;
    }

    float projection = DotProduct(minuss(point,Opoint),normalizing(vec));
    if(!(norm(mult(normalizing(vec),projection)) >= limit1 && norm(mult(normalizing(vec),projection)) <= limit2-limit1)){
        return backgroung;
    }

    float Dot = DotProduct(n, normalizing(light.LRay(point)));
    spec = powf(max(DotProduct(reflection_vector(normalizing(light.LRay(point)), n),normalizing(vec)), 0.f), gloss_factor);

    answer[0] = min(color[0]*(ambient + max(Dot,0.f)*diffuseStrength) + spec*specularStrength*255.f,255.f);
    answer[1] = min(color[1]*(ambient + max(Dot,0.f)*diffuseStrength) + spec*specularStrength*255.f,255.f);
    answer[2] = min(color[2]*(ambient + max(Dot,0.f)*diffuseStrength) + spec*specularStrength*255.f,255.f);

    return answer;
}

vector<float> CrossProduct( const vector<float>& a, const vector<float>& b){

    vector<float> answ;
    answ.push_back(Det2x2(a[1],a[2],b[1],b[2]));
    answ.push_back(-Det2x2(a[0],a[2],b[0],b[2]));
    answ.push_back(Det2x2(a[0],a[1],b[0],b[1]));

    return answ;
}


vector<float> pluss(const vector<float> &a, const vector<float> &b)
{
    vector<float> c(a.size());
    for(size_t i = 0; i < a.size(); ++i)
        c[i] = a[i] + b[i];
    return c;
}

vector<float> minuss(const vector<float>&a, const vector<float>&b)
{
    vector<float> c(a.size());
    for(size_t i = 0; i < a.size(); ++i)
        c[i] = a[i] - b[i];
    return c;
}

vector<float> mult(const vector<float>&a, const float &h)
{
    vector<float> c(a.size());
    for(size_t i = 0; i < a.size(); ++i)
        c[i] = a[i]*h;
    return c;
}


float norm(const vector<float> &a){

    return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}


vector<float> reflection_vector(const vector<float> &L, const vector<float> &N){

    return minuss(L, mult(N,2.f*DotProduct(L,N)));
}
