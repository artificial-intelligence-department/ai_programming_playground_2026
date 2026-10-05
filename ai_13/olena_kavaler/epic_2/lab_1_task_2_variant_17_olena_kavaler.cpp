/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "Введіть n: ";
    cin >> n;
    int m;
    cout << "Введіть m: ";
    cin >> m;

    // Спочатку віднімаємо поточне n від m, а потім зменшуємо n на 1
    int result = n---m;
    cout << result << endl;


    int n2;
    cout << "Введіть n: ";
    cin >> n2;
    int m2;
    cout << "Введіть m: ";
    cin >> m2;

    // Спочатку порівнюємо m2 < n2, а зменшення m2-- відбувається вже після порівняння.
    int result2 = m2--<n2;
    cout << result2 << endl;
    

    int n3;
    cout << "Введіть n: ";
    cin >> n3;
    int m3;
    cout << "Введіть m: ";
    cin >> m3;

    // Спочатку перевіряємо чи n3 > m3, і тільки після цього збільшуємо n3 на 1.
    int result3 = n3++>m3;
    cout << result3 << endl;

    return 0;

}
