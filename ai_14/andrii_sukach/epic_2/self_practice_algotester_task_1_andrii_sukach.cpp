/* Задача з алгостестера 
   Виконав: Сукач Андрій 
   Група: ШІ-14
   Коля, Вася і Теніс */

#include <iostream>

using namespace std;

int main() {
    long long n;
    int kolya_sets = 0, vasya_sets = 0, k = 0, v = 0;
    cin >> n;
    char c;

    for (long long i = 0; i < n; i++) {
        cin >> c; 
        if (c == 'K') {
            kolya_sets++;
        } else if (c == 'V') {
            vasya_sets++;
        } else {
            cout << "Не правильне значення" << endl;
            return 0;
        }

        // Перевірка завершення партії виконується ОДРАЗУ після кожної подачі
        if (kolya_sets >= 11 && (kolya_sets - vasya_sets) >= 2) {
            k++;
            kolya_sets = 0;
            vasya_sets = 0;
        } else if (vasya_sets >= 11 && (vasya_sets - kolya_sets) >= 2) {
            v++;
            kolya_sets = 0;
            vasya_sets = 0;
        }
    }

    // Вивід загального рахунку за партії (на Algotester виводять без пробілів навколо двоїкрапки)
    cout << k << ":" << v << endl;

    // Якщо остання партія не завершена, виводимо її рахунок
    if (kolya_sets > 0 || vasya_sets > 0) {
        cout << kolya_sets << ":" << vasya_sets << endl;
    }

    return 0;
}