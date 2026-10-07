#include <iostream>
using namespace std;

int main(){
    int n = 0;
    int m = 0;
    
    cout << "Введіть значення n:";
    cin >> n;
    cout << "Введіть значення m:";
    cin >> m;

    int a = n --- m;
    cout << "Результат обчислення n --- m: " << a << endl << "Значення n: " << n << endl<< "Значення m: " << m << endl;

    bool b = m-- < n; 
    cout << "Результат обчислення m-- < n: " << b << endl << "Значення n: " << n << endl << "Значення m: " << m << endl;

    bool c = n++ > m;
    cout << "Результат обчислення n++ > m: " << c << endl << "Значення n: " << n << endl << "Значення m: " << m << endl;
   

    return 0;
}