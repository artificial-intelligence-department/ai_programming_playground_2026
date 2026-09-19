#include <iostream>
using namespace std;
int main() {
    int a, b;
    cin >> a >> b;
    if (a < 0) {
        cout << "Помилка: Від'ємні числа не дозволені." << endl;
        return 1; 
    }
    if (b > 100) {
        cout << "Помилка: Ділення на число, яке перевищує 100, не дозволене." << endl;
        return 1; 
    }

    int result = a + b;
    cout << result << endl;

    return 0; // 
}