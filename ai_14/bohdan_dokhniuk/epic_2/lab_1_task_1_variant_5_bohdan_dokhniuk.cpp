
/*  
Lab 1 Task 1
Дохнюк Богдан 
ШІ-14
Варіант 5 
*/
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
//Обчислення для типу даних float
    
float a1 = 1000, b1 = 0.0001;
float c1, d1, e1, f1, g1, chys1, znam1, res1;
    
    
c1 = pow(a1 - b1, 3);       // (a-b)^3
d1 = pow(a1, 3);            // a^3
e1 = 3 * a1 * a1 * b1;      // 3a^2b
chys1 = c1 - (d1 - e1);     // чисельник
f1 = pow(b1, 3);            // b^3
g1 = 3 * a1 * b1 * b1;      // 3ab^2
znam1 = f1 - g1;            // знаменник
res1 = chys1 / znam1;

cout << "Тип float:" << endl;
cout << "Результат = " << res1 << endl;

//Обчислення для типу даних double 
double a2 = 1000, b2 = 0.0001;
double c2, d2, e2, f2, g2, chys2, znam2, res2;

c2 = pow(a2 - b2, 3);
d2 = pow(a2, 3);
e2 = 3 * a2 * a2 * b2;
chys2 = c2 - (d2 - e2);
f2 = pow(b2, 3);
g2 = 3 * a2 * b2 * b2;
znam2 = f2 - g2;
res2 = chys2 / znam2;

cout << endl << "Тип double:" << endl;
cout << "Результат = " << res2 << endl;

    return 0;
}