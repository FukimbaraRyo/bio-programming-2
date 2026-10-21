#include <iostream>
#include <cmath>
using namespace std;

int main(void){
    double x0;
    double x;
    int count;

    x0 = 0;
    count = 0;

    while(count < 100){
        x = x0 - (exp(x0)+ x0 - 5)/(exp(x0) + 1);
        count++;

        if(fabs(x - x0) < 1e-12){
            x0 = x;
            break;
        }

        x0 = x;
    }
    cout << "f1の解: " << x << endl;
    cout << "繰り返しの回数: " <<  count << endl;

    x0 = -0.1;
    count = 0;

    while (count < 1000) {
        x = x0 - (3 * x0);
        count++;

        if(fabs(x - x0) < 1e-12){
            x0 = x;
            break;
        }

        x0 = x;
    }
    cout << "f2の解: " << x << endl;
    cout << "繰り返しの回数: " << count << endl;

    return 0;

}

//実行結果↓
//f1の解: 1.30656
//繰り返しの回数: 7
//f2の解: -1.07151e+300
//繰り返しの回数: 1000

//繰り返しの回数は二分法よりも少ない回数で解がもとまった。
//しかし、f２においては x = -2 * x0 になることから初期値を代入すると遠ざかってしまう。
//ニュートン法は常に解を求められるのではなく、関数の性質によって結果が変わる。