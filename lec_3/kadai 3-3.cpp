#include <iostream>
#include <cmath>
using namespace std;

double f1(double x){
    return exp(x) + x -5;
}
double f2(double x){
    return cbrt(x);
}
int main(void){
    double a, b, c;
    int count;

    a = 0;
    b = 2;
    count = 0;

    while(b-a > 1e-12){
        c = (a+b) / 2;

        if(f1(c) == 0){
            a = c;
            b = c;
        }else if (f1(c) > 0){
            b = c;
        }else{
            a = c;
        }
        count++;
    }
    cout << "f1の解: " << (a+b) / 2 << endl;
    cout << "繰り返しの回数: " << count << endl;

    a = -0.1;
    b = 0.2;
    count = 0;

    while(b-a > 1e-12){
        c = (a+b) / 2;

        if(f2(c) == 0){
            a = c;
            b = c;
        }else if (f2(c) > 0){
            b = c;
        }else{
            a = c;
        }
        count++;
    }
    cout << "f2の解: " << (a+b) / 2 << endl;
    cout << "繰り返しの回数: " << count << endl;

    return 0;
}


//実行結果↓
//f1の解: 1.30656
//繰り返しの回数: 41
//f2の解: -9.09495e-14
//繰り返しの回数: 39