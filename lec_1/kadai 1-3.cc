#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(void){
  int a;
  int b;
  cin >> a >> b;
  int sum = a+b;
  cout << "和は" << sum << "です。" << endl;

  ifstream ist("input.txt");
  if(!ist){
    cout << "Cannot open input.txt" << endl;
    exit(1);
  }
  string s;
  ist >> s;
  ist.close();

  ofstream ost("output.txt");
  if(!ost){
    cerr << "Cannot open output.txt" << endl;
    exit(1);
  }
  ost.close();

  return 0;
}