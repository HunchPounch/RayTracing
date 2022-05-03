#include <iostream>
using namespace std;
#include "CObject.h"
#include "CFactory.h"
#include "functions.h"
#include "CLight.h"
#include "CFactorySphere.h"
#include "CFactoryBox.h"
#include "CFactoryTetra.h"
#include "template.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define PI 3.14159265
#include <omp.h>
#include <algorithm>
#include "template.h"
typedef map<string, CFactory*> objects;


void ReadFileObjects(const string name, vector<Object*> &v, map<string, CFactory*> &objects){

    ifstream fin(name);
    string str;
    int dim;
    string type;
    string fname;
    vector<float> buffer;
    int i=0;
    while(getline(fin,str)){

        if(i!=0) {
            buffer.clear();
        }

        stringstream ss(str);
        stringstream sss(str);
        dim = Size(sss)-1;
        istream_iterator<string> it;
        it = ss;

        if(it!=istream_iterator<string>()){
            type = (*it);
            ++it;
            i = 0;

            while(i<dim && it!=istream_iterator<string>()){

                buffer.push_back(stof(*it));
                i++;
                ++it;
            }

            Object *w = objects[type]->Create(buffer);
            v.push_back(w);
        }

    }
}


void color_distribution(vector<Object*> &v, const vector<float> &cam){

    float bufdist = -1;
    float s = (float)(v.size()-1);
    vector<float> col(3);
    int i = 0;
    for(vector<Object*>::iterator it = v.begin(); it!=v.end(); ++it){
        (*it)->SetDistToCam(cam);
    }

    sort(v.begin(),v.end());

    for(vector<Object*>::iterator it = v.begin(); it!=v.end(); ++it){
        if(i==0){
            col[0] = 64.f;
            col[1] = 64.f;
            col[2] = 64.f;
            (*it)->SetColor(col);
            i++;
            bufdist = (*it)->GetDistToCam();
            continue;
        }
        if(i==s){
            col[0] = 191.f;
            col[1] = 191.f;
            col[2] = 191.f;
            (*it)->SetColor(col);
            i++;
            break;
        }

        if(is_similar((*it)->GetDistToCam(),bufdist)){
            col[0] = 64.f + ((i-1)/s)*(191.f-64.f);
            col[1] = 64.f + ((i-1)/s)*(191.f-64.f);
            col[2] = 64.f + ((i-1)/s)*(191.f-64.f);
            (*it)->SetColor(col);
            i--;
            continue;
        }
        col[0] = 64 + (i/s)*(191-64);
        col[1] = 64 + (i/s)*(191-64);
        col[2] = 64 + (i/s)*(191-64);
        (*it)->SetColor(col);
        bufdist = (*it)->GetDistToCam();
        i++;
    }
}

void paint_over(const string name, vector<Object*> &v){

    ifstream fin(name);
    string buf;
    float bbuf;
    vector<float> cam;
    vector<float> normal; // от точки!!!!!!!!!!!!!!!
    vector<float> up;
    vector<float> col(3);
    float r;
    float limit;
    float alpha;
    int width;
    int height;
    Light light;

    map<string, int> mapping;

    mapping["cam"]  = 0;
    mapping["normal"]  = 1;
    mapping["up"]  = 2;
    mapping["screen"]  = 3;
    mapping["limit"]  = 4;
    mapping["alpha"]  = 5;
    mapping["width"]  = 6;
    mapping["height"]  = 7;
    mapping["light"]  = 8;

    for(int i=0; i<9; i++){
        fin >> buf;
        switch(mapping[buf]) {
        case 0:
            fin >> bbuf;
            cam.push_back(bbuf);
            fin >> bbuf;
            cam.push_back(bbuf);
            fin >> bbuf;
            cam.push_back(bbuf);
            continue;
        case 1:
            fin >> bbuf;
            normal.push_back(bbuf);
            fin >> bbuf;
            normal.push_back(bbuf);
            fin >> bbuf;
            normal.push_back(bbuf);
            continue;
        case 2:
            fin >> bbuf;
            up.push_back(bbuf);
            fin >> bbuf;
            up.push_back(bbuf);
            fin >> bbuf;
            up.push_back(bbuf);
            continue;
        case 3:
            fin >> r;
            continue;
        case 4:
            fin >> limit;
            continue;
        case 5:
            fin >> alpha;
            continue;
        case 6:
            fin >> width;
            continue;
        case 7:
            fin >> height;
            continue;
        case 8:

            fin >> bbuf;
            light.push_b(bbuf);
            fin >> bbuf;
            light.push_b(bbuf);
            fin >> bbuf;
            light.push_b(bbuf);
            continue;
        }

    }
    float physH = tan(alpha*PI/180)*r;
    float dimpix = physH/((float)height);
    float physW = dimpix*((float)width);

    vector<float> n4(normalizing(normal));
    vector<float> B;
    B.push_back(cam[0]+n4[0]*r);
    B.push_back(cam[1]+n4[1]*r);
    B.push_back(cam[2]+n4[2]*r);
    vector<float> AB = minuss(B, cam);
    float Cx = -physW/2+(dimpix/2);
    float Cy = physH/2-(dimpix/2);
    vector<float> Buf;
    int index = 0;
    unsigned char data[height*width*3];
    int j = 1;
    int i=1;
    color_distribution(v,cam);

#pragma omp parallel
    {
        vector<float> buf(3);
        vector<float> AD(3);
        vector<float> n1(normalizing(normal));
        vector<float> n2(normalizing(up));
        vector<float> n3(normalizing(CrossProduct(n1,n2)));

#pragma omp for private(i,j,Cx,Cy,index)
        for (int in = 1; in <= height*width; in++)
        {
            i = in/width + 1;
            j = in-(i-1)*width;

            Cx = -physW/2 + dimpix/2 + (j-1)*(dimpix);
            Cy = physH/2 - dimpix/2 - (i-1)*(dimpix);

            AD[0] = AB[0]+n2[0]*Cy+n3[0]*Cx;
            AD[1] = AB[1]+n2[1]*Cy+n3[1]*Cx;
            AD[2] = AB[2]+n2[2]*Cy+n3[2]*Cx;

            index = j*3 + (i-1)*width*3 -3;

            buf = GetRayCol(cam,AD,v,light,r,limit);

            data[index++] = (unsigned char)buf[0];
            data[index++] = (unsigned char)buf[1];
            data[index] = (unsigned char)buf[2];

        }
    }
    stbi_write_bmp("out.bmp", width, height, 3, data);

}




int main()
{
    string name1;
    string name2;
    cout << "Please enter name of file for parameters" << endl;
    cin >> name1;
    cout << "Please enter name of file for objects" << endl;
    cin >> name2;
    vector<Object*> v;
    map<string, CFactory*> objects;
    objects["Sphere"] = new CFactorySphere;
    objects["Box"] = new CFactoryBox;
    objects["Tetra"] = new CFactoryTetra;

    ReadFileObjects(name2, v, objects);

    paint_over(name1,v);

    for(vector<Object*>::iterator it = v.begin(); it!=v.end(); ++it){
        delete *it;
    }

    return 0;
}
