
/* 
Епік 2. Лабораторна робота 1. Варіант 23. Завдання 2.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {

    int n = 0;
    int m = 0;

    cout << "Введіть значення n і m: ";
    cin >> n >> m;

    // Обчислення виразу n---m, тобто (n--) - m
    int result1 = (n--) - m;
    cout << "Результат n---m = " << result1 << endl;
    cout << "Після n---m: n = " << n << ", m = " << m << endl;

    // Обчислення виразу m--<n
    bool result2 = m-- < n;
    cout << boolalpha;
    cout << "Результат m--<n = " << result2 << endl;
    cout << "Після m--<n: n = " << n << ", m = " << m << endl;

    // Обчислення виразу n++>m
    bool result3 = n++ > m;
    cout << "Результат n++>m = " << result3 << endl;
    cout << "Після n++>m: n = " << n << ", m = " << m << endl;

    return 0;
}