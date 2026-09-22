#include <iostream>
using namespace std;

int main() {
    long long n;
    cout << "Введіть кількість рядів: ";
    cin >> n;

    long long number = 0;

    for (long long i = 0; i < n; i++) {
        long long a;
        cin >> a;
        number += a - 1;
    }

    cout << "Кількість печива, які зможе з'їсти Марічка: " << number << endl;

    return 0;
}