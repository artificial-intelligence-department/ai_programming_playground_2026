#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    int a, b, c;
    cout << "Введіть а: " << endl;
    cin >> a;
    cout << "Введіть b: " << endl;
    cin >> b;
    cout << "Результат: " << endl;
    c=a+b;
    cout << c << endl;

    return 0;
}