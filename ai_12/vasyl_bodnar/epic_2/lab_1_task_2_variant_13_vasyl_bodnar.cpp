#include <iostream>

using namespace std;

int main() {

    int n;
    int m;
    cout << "Введіть значення n: " << endl;
    cin >> n;
    cout << "Введіть значення m: " << endl;
    cin >> m;

    int result_1 = m - ++n;
    cout << "Результат 1: " << result_1 << endl;

    bool result_2 = ++m > --n;
    cout << "Результат 2: " << boolalpha << result_2 << endl;

    bool result_3 = --n < ++m;
    cout << "Результат 3: " << boolalpha << result_3 << endl;

    return 0;
    
}
