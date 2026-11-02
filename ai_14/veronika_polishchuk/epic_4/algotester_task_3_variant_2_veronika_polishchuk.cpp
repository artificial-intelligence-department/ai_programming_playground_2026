/*
- Задача: Лабораторна робота алготестер 2, варіант 2
- Поліщук Вероніка
- Група 14
*/

#include <iostream>

using namespace std;

int main(){
    const int N = 100;
    int n, m, a[N], b[N];

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }

    int same = 0;
    
    // Перевірка кожного елемента першого масиву на наявність у другому
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i] == b[j]) {
                same++; // Збільшуємо лічильник, якщо знайдено збіг
                break;  // Перериваємо внутрішній цикл, щоб не рахувати дублікати
            }
        }
    }
    
    // Виведення кількості спільних елементів (перетин множин)
    cout << same << endl;
    
    cout << (n + m) - same;
    
    return 0;
}