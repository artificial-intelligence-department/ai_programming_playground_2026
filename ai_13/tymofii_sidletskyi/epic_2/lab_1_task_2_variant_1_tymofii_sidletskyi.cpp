#include <iostream>
using namespace std;
/* Задача 2 лаб 1 варіант 1
   Сідлецький Тимофій ШІ-13*/
int main () {
    int n, m;
    cout << "Введіть значення n: ";
    cin >> n;
    cout << "Введіть значення m: ";
    cin >> m;
    int a = n+++m;
    int b = m-- >n;
    int c = n-- >m;

    cout << "n+++m =  " << a << "\n";
    cout << "m-- >n = " << b << "\n";
    cout << "n-- >m = " << c << "\n";
}