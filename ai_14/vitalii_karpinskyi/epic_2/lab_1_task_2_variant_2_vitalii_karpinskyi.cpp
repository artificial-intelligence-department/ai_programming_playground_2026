#include <iostream>

using namespace std;

int main() {
    int n;
    int m;

    cout << "Введіть значення n: ";
    cin >> n;
    cout << "Введіть значення m: ";
    cin >> m;
    cout << endl;

    // Вираз 1
    int result1 = ++n * ++m;
    cout << "Результат виразу ++n * ++m: " << result1 << " (" << n << " * " << m << ")" << endl;

    cout << boolalpha;

    // Вираз 2
    bool result2 = m-- > n;
    cout << "Результат виразу m-- > n: " << result2 << " (" << m + 1 << " > " << n << ")" << endl;

    // Вираз 3
    bool result3 = n++ > m;
    cout << "Результат виразу n++ > m: " << result3 << " (" << n - 1 << " > " << m << ")" << endl;


    return 0;
}