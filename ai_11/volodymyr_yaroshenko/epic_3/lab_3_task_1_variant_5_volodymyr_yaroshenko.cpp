/*  
Лабораторна 3 завдання 1 
Варіант 5
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int factorial(int n) {
    if(n == 1 || n == 0) {
        return 1;
    }
    return n * factorial(n-1);
}
int main() {
   const int a = 1;
   const int b = 2;
   const double e = 0.0001;
double h = (b - a) / 10.0;
for(int i = 0; i <=10; i++ ) {
    double x = a + i * h;
    double sn = 0;
    double se = 0;
    int ne = 0;
    for(int n = 0; n < 15; n ++ ) {
        double temp = ((pow(x, n))/(factorial(n)));
        sn += temp;
    }
do {
se += ((pow(x, ne))/(factorial(ne)));
ne ++;
}
while((pow(x, ne))/(factorial(ne)) >= e) ;
 double y = exp(x);
cout << setprecision(8) << "x= " << x << endl;
cout << setprecision(8) << "sn= " << sn << endl;
cout << setprecision(8) << "se= " << se << endl;
cout << setprecision(8) << "y=  " << y << endl << '\n';
}
return 0;
}