/*
Алготестер лабораторна №6 варіант 1 (Без STL)
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int a[1005];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Спочатку видаляємо всі повтори (залишаємо тільки перше входження кожного числа)
    int uniq[1005];
    int m = 0;
    for (int i = 0; i < n; i++) {
        bool exists = false;
        for (int j = 0; j < m; j++) {
            if (uniq[j] == a[i]) {
                exists = true;
                break;
            }
        }
        if (exists == false) {
            uniq[m] = a[i];
            m++;
        }
    }

    // Сортуємо отриманий масив унікальних елементів за зростанням
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (uniq[j] > uniq[j + 1]) {
                int tmp = uniq[j];
                uniq[j] = uniq[j + 1];
                uniq[j + 1] = tmp;
            }
        }
    }

    // Обертаємо посортовану версію на K позицій вліво
    k = k % m;
    int rotated[1005];
    for (int i = 0; i < m; i++) {
        rotated[i] = uniq[(i + k) % m];
    }

    // Вивід результату
    cout << m << endl;
    for (int i = 0; i < m; i++) {
        cout << rotated[i] << (i + 1 < m ? " " : "\n");
    }

    return 0;
}