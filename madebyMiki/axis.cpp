#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {

    ofstream ofs("axis.ply");
    
    ofs << "ply\n" << "format ascii 1.0\n" << "element vertex 1999\n" << "property float x\n"
    << "property float y\n" << "property float z\n" << "property uchar diffuse_red\n"
    << "property uchar diffuse_green\n" << "property uchar diffuse_blue\n" << "end_header\n";
    
    for(double i=0.01; i<20; i+=0.01){
        //x軸は赤
        ofs << i << " " << 0 << " " << 0 << " " << 255 << " " << 0 << " " << 0 << endl;
        ofs << -i << " " << 0 << " " << 0 << " " << 100 << " " << 0 << " " << 0 << endl;
        //y軸は緑
        ofs << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << " " << 0 << endl;
        ofs << 0 << " " << -i << " " << 0 << " " << 0 << " " << 100 << " " << 0 << endl;
        //z軸は青
        ofs << 0 << " " << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << endl;
        ofs << 0 << " " << 0 << " " << -i << " " << 0 << " " << 0 << " " << 100 << endl;
    }
    
    return 0;
}