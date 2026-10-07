#include <iostream>
using namespace std;

class Matrix{
public:
  double a,b,c,d;
  void set(double x, double y, double z, double w){
    a = x;
    b = y;
    c = z;
    d = w;
  };
  Matrix add(Matrix &q){
    Matrix m;
    m.a = a + q.a;
    m.b = b + q.b;
    m.c = c + q.c;
    m.d = d + q.d;
  
  return(m);
  }
  Matrix mult(Matrix &q){
    Matrix m;
    m.a = a * q.a + b * q.c;
    m.b = b * q.b + b * q.d;
    m.c = c * q.a + d * q.c;
    m.d = c * q.b + d * q.d;
  return(m);
  }
  double trace(void){
    return a+d;
  }
  Matrix inverse(void){
    double x = a*d - b*c;
    Matrix m;
    m.a = d / x;
    m.b = -b / x;
    m.c = -c / x;
    m.d = a / x;
  return(m);
  }
 };

 int main(void){
    Matrix p;
    p.set(1, 2, 3, 4);

    cout << "トレースは" << p.trace() << endl;

    Matrix p_inv = p.inverse();

    cout << p_inv.a << " " << p_inv.b << endl;
    cout << p_inv.c << " " << p_inv.d << endl;

    return 0;
}