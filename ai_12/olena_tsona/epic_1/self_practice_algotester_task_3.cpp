#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int cells = n * m;

    // Якщо кількість клітинок непарна, перемагає Imp, якщо парна — Dragon
    if (cells % 2 != 0) {
        cout << "Imp" << endl;
    } else {
        cout << "Dragon" << endl;
    }

    return 0;
}