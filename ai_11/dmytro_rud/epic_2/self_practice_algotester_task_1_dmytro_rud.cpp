#include <iostream>
#include <string>

using namespace std;

int main() {
    string n;
    cin >> n; // Зчитуємо номер як рядок

    // Шукаємо підрядок "47"
    if (n.find("47") != string::npos) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
