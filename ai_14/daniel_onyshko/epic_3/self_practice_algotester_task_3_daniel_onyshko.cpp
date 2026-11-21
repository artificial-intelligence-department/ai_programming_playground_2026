/*Марічка і смачні цукерки
Онишко Даніель
*/

#include <iostream>

// використовуємо глобальні масиви з іншим розміром та іменами
int arr_val[100005];
int freq[100005];

int main() {
    int total_items, limit_k;
    if (!(std::cin >> total_items >> limit_k)) return 0;

    // зчитування та підрахунок частот в одному циклі з іншим стилем індексації
    for (int idx = 0; idx < total_items; ++idx) {
        std::cin >> arr_val[idx];
        freq[arr_val[idx]]++;
    }

    int dominant_val = -1;
    bool achievable = false;

    // перебір можливих значень типів 
    for (int candidate = 1; candidate <= 100000; ++candidate) {
        if (freq[candidate] >= limit_k) {
            dominant_val = candidate;
            achievable = true;
            break; // знаходимо першу підходящу і зупиняємось (оптимізація)
        }
    }

    if (!achievable) {
        std::cout << "Oh sh*t\n";
        return 0;
    }

    // вивід спочатку елементів основного  в один зручний прохід
    for (int idx = 0; idx < total_items; ++idx) {
        if (arr_val[idx] == dominant_val) {
            std::cout << arr_val[idx] << " ";
        }
    }

    // вивід решти елементів який відрізняються від основного типу
    for (int idx = 0; idx < total_items; ++idx) {
        if (arr_val[idx] != dominant_val) {
            std::cout << arr_val[idx] << " ";
        }
    }

    std::cout << "\n";

    return 0;
}