
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {

    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int* even = new int[n];
    int evencount = 0;
    int* odd = new int[n];
    int oddcount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even[evencount] = arr[i];
            evencount++;
        } else {
            odd[oddcount] = arr[i];
            oddcount++;
        }
    }

    if (abs(evencount - oddcount) > 1) {
        cout << "-1" << endl;
        delete[] arr;
        delete[] even;
        delete[] odd;
        return 0;
    }

    // true - зараз черга парного, false - зараз черга непарного
    // починаємо з парних, якщо їх більше або порівну
    bool evenfirst = (evencount >= oddcount);
    int ei = 0;
    int oi = 0;

    for (int i = 0; i < n; i++) {
        if (evenfirst) {
            cout << even[ei] << " ";
            ei++;
        } else {
            cout << odd[oi] << " ";
            oi++;
        }
        evenfirst = !evenfirst; // передаємо чергу іншому типу
    }
    cout << endl;


    delete[] arr;
    delete[] even;
    delete[] odd;

    return 0;
}