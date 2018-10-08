#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<iomanip>
#include<sstream>
#include<vector>
#include<string>
#include<random>

using namespace std;

// << split処理 >>
// 文字列 src を key で分割する。
// vector型 の配列で結果が戻る。
vector<string> split( string &src, string key){
    vector<string> v;
    string str = src;

    int index = 0;
    while(index < (int)str.length()){
        int oldindex = index;
        index = str.find( key, index);
        if(index != string::npos){
            string item = str.substr(oldindex, index - oldindex);
            v.push_back(item);
        }
        else{
            string item = str.substr(oldindex);
            v.push_back(item);
            break;
        }
        index += key.length();
    }
    return v;
}


int main(int argc, char* argv[]){

  if(argc != 3){
    cout << "Argument Error!" << endl;
    return 0;
  }

  ifstream ifs_gene(argv[1]);
  if(!ifs_gene){
    cout << "Error! " << argv[1] <<" can't be opened"<< endl;
  }

  ifstream ifs_coordinate(argv[2]);
  if(!ifs_coordinate){
    cout << "Error! " << argv[2] <<" can't be opened" << endl;
  }

  //遺伝子情報をvectorに入れる
  string line_string;
  char line[255];
  vector<string> gene;
  ifs_gene.getline(line, sizeof(line));
  line_string = line; // string型に変換する。
  gene = split(line_string, ",");
  for(int i = 0 ; i < gene.size() ; i++){
  cout << gene[i] << " ";
  }
  cout << endl;

  cout << gene[0] << endl;
  cout << stoi(gene[0]) << endl;

  int pinched_count = 0;
  for(int i = 0 ; i < gene.size() ; i++){
    if(stoi(gene[i]) != 0){
      pinched_count++;
    }
  }
  cout << pinched_count << endl << endl;

  //座標情報の取得と書き込み
  //乱数の用意
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<double> rand_e(-1, 1);
  uniform_real_distribution<double> rand_theta(0, 2*M_PI);

  //出力plyファイル作成
  ostringstream ostr_pinching,ostr_pinched;

  ostr_pinching << "Pinching_" << argv[2] << ".ply";
  ostr_pinched  << "Pinched_" << argv[2] << ".ply";

  ofstream ofs_pinching(ostr_pinching.str());
  ofstream ofs_pinched(ostr_pinched.str());

  //plyファイルのヘッダ宣言
  ofs_pinching << "ply\n" << "format ascii 1.0\n" << "element vertex 401000\n"
               << "property float x\n" << "property float y\n" << "property float z\n"
               << "property uchar diffuse_red\n" << "property uchar diffuse_green\n" << "property uchar diffuse_blue\n"
               << "end_header\n";

  int pinched_vertex = 1000 + pinched_count*10000;
  ofs_pinched << "ply\n" << "format ascii 1.0\n" << "element vertex "<< pinched_vertex <<"\n"
             << "property float x\n" << "property float y\n" << "property float z\n"
             << "property uchar diffuse_red\n" << "property uchar diffuse_green\n" << "property uchar diffuse_blue\n"
             << "end_header\n";

  //花軸を生成(z軸上青色)
  for(double i=-5; i<=5; i+=0.01){
      ofs_pinching << 0 << " " << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << "\n";
      ofs_pinched  << 0 << " " << 0 << " " << i << " " << 0 << " " << 0 << " " << 255 << "\n";
  }


  vector<string> coordinate;
  int gene_num = 0;
  while( !ifs_coordinate.eof() ){
        cout << gene_num << endl;
        ifs_coordinate.getline(line, sizeof(line));
        line_string = line; // string型に変換する。
        coordinate = split(line_string, ",");
        for(int i = 0 ; i < coordinate.size() ; i++){
          cout << coordinate[i] << " ";
        }
        cout << endl;

        if(gene[gene_num] == "0"){
          //重心を入力
          ofs_pinching << coordinate[0] << " "<< coordinate[1] << " " << coordinate[2] << " " << 0 << " " << 0 << " " << 255 << "\n";

          //球形成
          for(double k=1; k<=9999; k+=1){
            double e = rand_e(mt);
            double theta = rand_theta(mt);

            double x = stod(coordinate[0]) + sqrt(1-pow(e,2)) * cos(theta) ;
            double y = stod(coordinate[1]) + sqrt(1-pow(e,2)) * sin(theta) ;
            double z = stod(coordinate[2]) + e ;
            ofs_pinching << x << " "<< y << " " << z <<  " " << 0 << " " << 0 << " " << 255 << "\n";
          }
        }
        else{
          //重心を入力
          ofs_pinching << coordinate[0] << " "<< coordinate[1] << " " << coordinate[2] << " " << 0 << " " << 255 << " " << 0 << "\n";
          ofs_pinched  << coordinate[0] << " "<< coordinate[1] << " " << coordinate[2] << " " << 0 << " " << 255 << " " << 0 << "\n";
          //球形成
          for(double k=1; k<=9999; k+=1){
            double e = rand_e(mt);
            double theta = rand_theta(mt);

            double x = stod(coordinate[0]) + sqrt(1-pow(e,2)) * cos(theta) ;
            double y = stod(coordinate[1]) + sqrt(1-pow(e,2)) * sin(theta) ;
            double z = stod(coordinate[2]) + e ;
            ofs_pinching << x << " "<< y << " " << z <<  " " << 0 << " " << 255 << " " << 0 << "\n";
            ofs_pinched  << x << " "<< y << " " << z <<  " " << 0 << " " << 255 << " " << 0 << "\n";
          }

        }

        gene_num++;
  }


  return 0;
}
