#include <iostream>
#include <cmath>
using namespace std;

int main(void){
    float a = 1, b = 10000, c = 1;
    float d = sqrt(b*b - 4*a*c);
    float x1, x2;

    x1 = (-b + d) / (2*a);
    x2 = (-b - d) / (2*a);

    cout << "通常の場合: " << x1 << "," << x2 << endl;

    float q;
    if(b >= 0) {
        q = -0.5 * (b + d);
    } else {
        q = -0.5 * (b - d);
    }
    x1 = q / a;
    x2 = c / q;

    cout << "配慮した場合: " << x1 << "," << x2 << endl;

    return 0;
}

//実行結果↓
//通常の場合: 0,-10000
//配慮した場合: -10000,-0.0001
//通常の場合の０は本来は０でない非常小さい値が正しく計算されなかったものだと考えられる。