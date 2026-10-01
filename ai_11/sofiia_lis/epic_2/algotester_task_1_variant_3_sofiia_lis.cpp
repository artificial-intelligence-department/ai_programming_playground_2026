/* 
Епік 2. algotester_task_1_variant_3
Авторка: Софія Ліс
Група: ші-11
*/
#include <iostream>

using namespace std;

int main() {
    long long cubes[5]; // створила масив розмірністю 5
    for (int i = 0; i < 5; i++) { 
        cin >> cubes[i]; // заповнила елементи масиву значеннями
    }

    for (int i = 0; i < 5; i++) {
        if (cubes[i] <= 0) { // перевірила, чи не помилкове значення 
            cout << "ERROR" << endl;
            return 0;
        }

        if (i > 0 && cubes[i] > cubes[i - 1]) { // перевірила, чи не перший кубик і чи розмір поточного не більший за попередній
            cout << "LOSS" << endl;
            return 0;
        }
    }

    cout << "WIN" << endl; // перемога, якщо не було помилки чи програшу

    return 0;
}