/*  
Лабораторна робота завдання 2
Ярошенко Володимир 
11 група 
*/
#include <iostream>

using namespace std;

int main() {
int n; 
int m;
cout << "Введіть n та m: ";
cin >> n >> m;
int res1 = n++ -m; //
bool res2 = m-- >n;
bool res3 = n++ >m;
cout <<  "n++ - m = "<< res1 << endl;
cout << boolalpha ;
cout << "m-- >n = " << res2 << endl;
cout << "n++ >m = " << res3 << endl; 
cout << n << ' ' << m << endl;
return 0;
}
