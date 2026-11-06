/*
Задача: Алготестер. Лабораторна 2, варіант 1
Автор: Ольга Дрогомирецька
Група: ШІ-13
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int r[100000];
    
    //зчитую елемнти масиву
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    //якшо чисел не більше двох, мінімальна втома 0
    if (n <= 2) {
        cout << 0 << '\n';
        return 0;
    }
    //сортую масив бульбашкою за зростанням
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (r[j] > r[j + 1]) {
                int temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
    //після видалення найменшого числа мінімумом стане r[1]
    int withoutMin = r[n - 1] - r[1];
    //після видалення найбільшого числа максимумом стане r[n-2]
    int withoutMax = r[n - 2] - r[0];
    //виводжу меншу з двох різниць
    if (withoutMin < withoutMax) {
        cout << withoutMin << '\n';
    } else {
        cout << withoutMax << '\n';
    }

    return 0;
}