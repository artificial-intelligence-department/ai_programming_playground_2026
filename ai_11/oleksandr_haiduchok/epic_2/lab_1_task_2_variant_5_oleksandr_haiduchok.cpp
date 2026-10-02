#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n = 0;
    int m = 0;
    cout << "Введіть значення n:";
    cin >> n;
    cout << "Введіть значення m:";
    cin >> m;

    int a = 0;
    int b = 0;
    int c = 0;


    a = - (-m) - ++n;
    
    cout << "Результат дії 1:" << a << endl;

    b = (m * n) < n;
    n++;

    cout << "Результат дії 2:" << b << endl;

    c = n-- > m++;

     cout << "Результат дії 3:" << c << endl;

     return 0;
}
