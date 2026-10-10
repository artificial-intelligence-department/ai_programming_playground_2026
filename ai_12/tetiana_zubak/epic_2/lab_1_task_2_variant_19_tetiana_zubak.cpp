/* 
Лаборторна робота, завдання 2, варіант 19
Зубак Тетяна
ШІ-12
*/
#include <iostream>

using namespace std;

int main() {
    int m, n;

    cout << "Введіть значення m: ";
    cin >> m;
    cout << "Введіть значення n: ";
    cin >> n;
    
    int one = - -m - ++n;
    bool two = (m * n) < n++;
    bool three = n-- > m++;

    cout << "1)- -m - ++n = " << one << endl;
    cout << "2)m * n < n++ = " << two << endl;
    cout << "3)n-- > m++ = " << three << endl;

    return 0;
}