#include <iostream>
using namespace std;

int main() {
    //розміри дошки
    int n, m;
    if (cin >> n >> m) {
        //перевірка на парність площі дошки
        if ((n * m) % 2 != 0) {
            cout << "Imp\n";
        } else {
            cout << "Dragon\n";
        }
    }
    return 0;
}