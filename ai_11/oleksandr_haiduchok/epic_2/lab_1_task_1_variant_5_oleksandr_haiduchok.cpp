#include <iostream>
#include <cmath>

using namespace std;

int main(){
// до кожної змінної вказую тип даних, у якому будуть проводитись обрахунки
    //задаємо значення змінним
    float a = 1000;
    float b = 0.0001;
// розвʼязуємо першу дужку чисельника
    float q = a - b;
    float w = pow(q,3);
// розвʼязуємо другу дужку чисельника
    float e = pow(a,3);
    float r = 3*a*a*b;
    float t = e - r;
//віднімаємо результати обрахунку першої та другої дужки
    float y = w - t;
//обраховуємо знаменник
    float u = pow(b,3);
    float i = 3*a*b*b;
    float o = u - i;
// ділимо чисельник на знаменник
    float p = y / o;

    cout << p << endl;


    
    
    double a1 = 1000;
    double b1 = 0.0001;

    double q1 = a1 - b1;
    double w1 = pow(q1,3);

    double e1 = pow(a1,3);
    double r1 = 3*a1*a1*b1;
    double t1 = e1 - r1;

    double y1 = w1 - t1;

    double u1 = pow(b1,3);
    double i1 = 3*a1*b1*b1;

    double o1 = u1 - i1;

    double p1 = y1 / o1;

    cout << p1 << endl;

    return 0;


}