#include <iostream>

using namespace std;

int main() {
    int origin_n;
    int origin_m;

    cout << "Введіть значення n: ";
    cin >> origin_n;
    cout << "Введіть значення m: ";
    cin >> origin_m;
    cout << endl;

    // Вираз 1
    int n = origin_n;
    int m = origin_m;
    int result1 = ++n * ++m;
    cout << "Результат виразу ++n * ++m: " << result1 << " (" << n << " * " << m << ")" << endl;

    cout << boolalpha;

    // Вираз 2
    n = origin_n;
    m = origin_m;
    bool result2 = m-- > n;
    cout << "Результат виразу m-- > n: " << result2 << " (" << origin_m << " > " << n << ")" << endl;

    // Вираз 3
    n = origin_n;
    m = origin_m;
    bool result3 = n++ > m;
    cout << "Результат виразу n++ > m: " << result3 << " (" << origin_n << " > " << m << ")" << endl;


    return 0;
}