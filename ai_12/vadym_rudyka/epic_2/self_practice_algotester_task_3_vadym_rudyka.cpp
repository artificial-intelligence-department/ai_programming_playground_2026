#include <iostream>

using namespace std;

int main() {
    // розміри дошки
    int n,m;
    cin >> n >> m;
    // перевірка, чи кількість клітинок на дошці парна чи непарна, щоб визначити, хто виграє
    if (n*m % 2 == 0) {
        cout << "Dragon";
    } else {
        cout << "Imp";
    }

    return 0;
}