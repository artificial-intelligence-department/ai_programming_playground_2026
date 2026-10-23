//Задача Алготестер "Цікава гра"
#include <iostream>
using namespace std;
int main() {
    int n;
    int m;
    int sum;
    cin >> n >> m;
    sum = m * n;
    // Бісеня виграє тоді, коли непарна кількість клітинок
    if (sum % 2 == 0 ) {
        cout << "Dragon" << endl;
    }
    else {
        cout << "Imp" << endl;
    }
    return 0;
}