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
  uniform_real_distribution<double> rand_theta(0 , 2*M_PI);
  uniform_real_distribution<double> rand_center4(-4 , 4);
  uniform_real_distribution<double> rand_center3(-3 , 3);
  uniform_real_distribution<double> rand_center2(-2 , 2);
  uniform_real_distribution<double> rand_center1(-1 , 1);
  uniform_real_distribution<double> rand_z(-7 , 7);
  uniform_real_distribution<double> rand_centerimpossible(4 , 7);
  uniform_real_distribution<double> rand_zimpossible(10 , 12);

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
  ostr_ply << "kyohoumodel+impossible_" << result <<".ply";
  ostr_csv << "kyohoumodel+impossible_" << result <<".csv";

  ofstream ofs_ply(ostr_ply.str());
  ofstream ofs_csv(ostr_csv.str());

  //plyファイルのヘッダ宣言
  ofs_ply << "ply\n" << "format ascii 1.0\n" << "element vertex 401000\n"
          << "property float x\n" << "property float y\n" << "property float z\n"
          << "property uchar diffuse_red\n" << "property uchar diffuse_green\n" << "property uchar diffuse_blue\n"
          << "end_header\n";

  //ofs_csv << "花軸" << "\n";

  //花軸を生成(z軸上青色，vertex1000)>>巨峰は15段なので[-7:7]で花軸を置く
  int count_vertex = 0;
  for(double i=-7; i<=7; i+=0.01){
      ofs_ply << 0 << " " << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << "\n";
      count_vertex++;
      if(count_vertex == 1000){break;} //vertex1000が15で割れないからbreak
      //ofs_csv << 0 << " " << 0 << " " << i << "\n";
  }

  //ofs_csv << "重心" << "\n";

  //実を生成
  //model重心座標の各成分を生成(花軸の範囲内)
  int count_stage = 1;
  double center_x , center_y , center_z;
  for(int i=1; i<=36; i+=1){
    switch (count_stage) {
      case 1 :  center_z = 7;
                center_x = rand_center4(mt);
                center_y = rand_center4(mt);
                break;
      case 2 :  center_z = 6;
                center_x = rand_center4(mt);
                center_y = rand_center4(mt);
                break;
      case 3 :  center_z = 5;
                center_x = rand_center4(mt);
                center_y = rand_center4(mt);
                break;
      case 4 :  center_z = 4;
                center_x = rand_center3(mt);
                center_y = rand_center3(mt);
                break;
      case 5 :  center_z = 3;
                center_x = rand_center3(mt);
                center_y = rand_center3(mt);
                break;
      case 6 :  center_z = 2;
                center_x = rand_center3(mt);
                center_y = rand_center3(mt);
                break;
      case 7 :  center_z = 1;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;
      case 8 :  center_z = 0;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;
      case 9 :  center_z = -1;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;

      case 10:  center_z = -2;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;
      case 11:  center_z = -3;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;
      case 12:  center_z = -4;
                center_x = rand_center2(mt);
                center_y = rand_center2(mt);
                break;
      case 13:  center_z = -5;
                center_x = rand_center1(mt);
                center_y = rand_center1(mt);
                break;
      case 14:  center_z = -6;
                center_x = rand_center1(mt);
                center_y = rand_center1(mt);
                break;
      case 15:  center_z = -7;
                center_x = rand_center1(mt);
                center_y = rand_center1(mt);
                break;
    }
    if(i == 4||i==8||i==12||i==15||i==18||i==21||i==23||i==25||i==27||i==29||i==31||i==33||i==34||i==35||i==36){count_stage++;}

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

  //impossible重心座標の各成分を生成(花軸の範囲内)
  for(int i=1; i<=4; i+=1){
    switch (i) {
      case 1 :  center_z = rand_zimpossible(mt);
                center_x = rand_center4(mt);
                center_y = rand_center4(mt);
                break;
      case 2 :  center_z = -rand_zimpossible(mt);
                center_x = rand_center4(mt);
                center_y = rand_center4(mt);
                break;
      case 3 :  center_z = rand_z(mt);
                center_x = rand_centerimpossible(mt);
                center_y = rand_centerimpossible(mt);
                break;
      case 4 :  center_z = rand_z(mt);
                center_x = rand_centerimpossible(mt);
                center_y = rand_centerimpossible(mt);
                break;
    }



    //重心を入力
    ofs_ply << center_x << " "<< center_y << " " << center_z << " " << 255 << " " << 0 << " " << 0 << "\n";
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
      ofs_ply << x << " "<< y << " " << z <<  " " << 255 << " " << 0 << " " << 0 << "\n";
    }

  }

  return 0;
}
