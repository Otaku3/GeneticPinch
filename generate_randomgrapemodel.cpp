#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<random>
#include<iomanip>
#include<sstream>

using namespace std;

int main(){

  //乱数の用意
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<double> rand_e(-1, 1);
  uniform_real_distribution<double> rand_center(-5,5);
  uniform_real_distribution<double> rand_theta(0, 2*M_PI);

  //現在日時を取得する
  time_t t = time(nullptr);

  const tm* lt = localtime(&t); //形式を変換する

  stringstream s; //sに独自フォーマットになるように連結していく
  s<<"20";
  s<<lt->tm_year-100; //100を引くことで20xxのxxの部分になる
  s<<"-";
  s<<lt->tm_mon+1; //月を0からカウントしているため
  s<<"-";
  s<<lt->tm_mday; //そのまま
  s<<"-";
  s<<lt->tm_hour;
  s<<":";
  s<<lt->tm_min;
  s<<":";
  s<<lt->tm_sec;

  string result = s.str();


  ostringstream ostr_ply,ostr_csv;

  ostr_ply << "grapemodel_" << result <<".ply";
  ostr_csv << "grapemodel_" << result <<".csv";

  ofstream ofs_ply(ostr_ply.str());
  ofstream ofs_csv(ostr_csv.str());

  //plyファイルのヘッダ宣言
  ofs_ply << "ply\n" << "format ascii 1.0\n" << "element vertex 401000\n"
          << "property float x\n" << "property float y\n" << "property float z\n"
          << "property uchar diffuse_red\n" << "property uchar diffuse_green\n" << "property uchar diffuse_blue\n"
          << "end_header\n";

  //ofs_csv << "花軸" << "\n";

  //花軸を生成(z軸上青色)
  for(double i=-5; i<=5; i+=0.01){
      ofs_ply << 0 << " " << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << "\n";
      //ofs_csv << 0 << " " << 0 << " " << i << "\n";
  }

  //ofs_csv << "重心" << "\n";

  //実を生成
  for(int i=1; i<=40; i+=1){
    //重心座標の各成分を生成(花軸の範囲内)
    double center_x = rand_center(mt);
    double center_y = rand_center(mt);
    double center_z = rand_center(mt);

    //重心を入力
    ofs_ply << center_x << " "<< center_y << " " << center_z << " " << 0 << " " << 255 << " " << 0 << "\n";
    ofs_csv << center_x << ","<< center_y << "," << center_z << "\n";
    //ログ用
    cout << center_x << " "<< center_y << " " << center_z << "\n";

    //重心から球を膨らませる(ビジュアライズのため)
    for(double k=1; k<=9999; k+=1){
      double e = rand_e(mt);
      double theta = rand_theta(mt);

      double x = center_x + sqrt(1-pow(e,2)) * cos(theta) ;
      double y = center_y + sqrt(1-pow(e,2)) * sin(theta) ;
      double z = center_z + e ;
      ofs_ply << x << " "<< y << " " << z <<  " " << 0 << " " << 255 << " " << 0 << "\n";
    }

  }


  return 0;
}
