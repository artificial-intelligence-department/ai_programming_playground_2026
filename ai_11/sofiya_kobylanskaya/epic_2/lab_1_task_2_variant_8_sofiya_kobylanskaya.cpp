/*
Епік 2. Лабораторна робота 1. Варіант 8. Завдання 2.
Автор: Кобилянська Софія
Група: ші-11
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    int m;

    cout << "Введіть значення n і m: " << endl;
    cin >> n >> m;

    int result_1 = (n++) - m;
    cout << "Результат n++ - m = " << result_1 << endl;
    cout << "Після n++ - m: n = " << n << ", m = " << m << endl;

    bool result_2 = (m--) > n;
    cout << boolalpha;
    cout << "Результат m-- > n = " << result_2 << endl;
    cout << "Після m-- > n: n = " << n << ", m = " << m << endl;

    bool result_3 = (n--) > m;
    cout << "Результат  n-- > m = " << result_3 << endl;
    cout << "Після  n-- > m: n = " << n << ", m = " << m << endl;

    return 0;
}