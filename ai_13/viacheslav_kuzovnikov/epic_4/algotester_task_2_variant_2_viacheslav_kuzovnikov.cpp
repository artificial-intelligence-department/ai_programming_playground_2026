/*
Контест
Лабораторна №2
Варіан №2
Кузовніков В'ячеслав Євгеніойович
ШІ-13
*/


#include <iostream>
using namespace std;

int main() {
    int size = 0;
    cin >> size;
    if ( size < 1 || size > 100000) {
        return 1;
    }

    int *mas = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> mas[i];
        if (mas[i] < 0 || mas[i] > 100000) {
            delete[] mas;
            return 1;
        }
    }

    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    if (
        a < 0 || a > 100000 || 
        b < 0 || b > 100000 || 
        c < 0 || c > 100000) {
        delete[] mas;
        return 1;
    }

    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (mas[i] != a && mas[i] != b && mas[i] != c) {
            new_size++;
        }
    }

    if (new_size < 2) {
        cout << 0 << endl;
    } else {
        int *mas_deleted = new int[new_size];

        int k = 0;
        for (int i = 0; i < size; i++) {
            if (mas[i] != a && mas[i] != b && mas[i] != c) {
                mas_deleted[k] = mas[i];
                k++;
            }
        }


            int size_sum = new_size - 1;
            int *mas_sum = new int[size_sum];

            for (int i = 0; i < size_sum; i++) {
                mas_sum[i] = mas_deleted[i] + mas_deleted[i + 1];
            }

            cout << size_sum << endl;
            for (int i = 0; i < size_sum; i++) {
                cout << mas_sum[i] << " ";
            }
        
            
        cout << endl;
         delete[] mas_sum; 
        delete[] mas_deleted;
    }

    delete[] mas;

    return 0;
}