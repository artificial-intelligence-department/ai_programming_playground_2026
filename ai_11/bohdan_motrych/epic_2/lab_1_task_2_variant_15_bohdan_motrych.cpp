#include <iostream>

using namespace std;

int main() {
    // Введення даних
    int n0 = 0, m0 = 0;
    cout << "Введіть значення m: ";
    cin >> m0;
    cout << "Введіть значення n: ";
    cin >> n0;

    int m = m0;
    int n = n0;
    // Обчислення
    int result_1 = n++ - m;
    m = m0, n = n0;

    bool result_2 = m-- > n;
    m = m0, n = n0;

    bool result_3 = n-- > m;
    m = m0, n = n0;
    // Виведення результатів
    cout << "n++ - m = " << result_1 << endl;
    cout << "m-- > n = " << result_2 << endl;
    cout << "n-- > m = " << result_3 << endl;

    return 0;
}