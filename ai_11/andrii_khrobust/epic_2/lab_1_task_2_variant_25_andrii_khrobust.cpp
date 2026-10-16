/* Задача: лабораторна робота, завдання 2 (варіант 25)
Хробуст Андрій
Група ШІ - 11
*/
#include <iostream>
using namespace std;

int main() {
int m,n,b,c,a;
cout<<"введіть значення m: ";
cin >> m ;
cout<<"введіть значення n: ";
cin >> n;
a=-- m-++n;
b=m* n < n++ ;
c= n -- > m++;
cout << a << endl;//1 вираз
cout << b << endl;//2 вираз
cout << c<<endl;//3 вираз
cout<<"m: "<<m<<endl;//вивід для m 
cout<<"n: "<<n<<endl;//вивід для n
return 0;
}