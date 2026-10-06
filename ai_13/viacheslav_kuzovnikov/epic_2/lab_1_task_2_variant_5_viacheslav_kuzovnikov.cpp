/*
Лабораторна №1
Завдання №2
Варіант №5
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){

    int n;
    int m;

    cout << "Введіть n: ";
    cin >> n;

    cout << "Введіть m: ";
    cin >> m;

    int a = (--m)-(++n);

    int b = (m*n) < (n++);

    int c = (n--) > (m++);

    cout << "1)  --m-++n = " << a << endl;
    cout << "2)  m*n<n++ =  " << b << endl;
    cout << "3)  n-- > m++ = " << c << endl;





    return 0;
}
