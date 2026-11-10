/*
Lab 4_2
Кузовніков В'ячеслав Євгенійович
ШІ - 13
Варіант 3
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n = 0;
    if (!(cin >> n)) return 0;

    int arr[n]; 
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    //partition — розділяємо масив на 3 частини за остачею від ділення на 3
    int* it1 = partition(arr, arr + n, [](int x) {
        return x % 3 == 0;
    });

    int* it2 = partition(it1, arr + n, [](int x) {
        return x % 3 == 1;
    });

    // sort — сортуємо кожну частину відповідно до умов

    sort(arr, it1);

    sort(it1, it2, greater<int>());

    sort(it2, arr + n);

    // unique — прибираємо підряд ідучі однакові елементи
    int* u1 = unique(arr, it1);
    int* u2 = unique(it1, it2);
    int* u3 = unique(it2, arr + n);

    // Перепаковуємо унікальні елементи в початок масиву
    int m = 0;

    for (int* p = arr; p != u1; p++) {
        arr[m++] = *p;
    }
    for (int* p = it1; p != u2; p++) {
        arr[m++] = *p;
    }
    for (int* p = it2; p != u3; p++) {
        arr[m++] = *p;
    }


    cout << m << endl;
    for (int i = 0; i < m; i++) {
        cout << arr[i] << " ";
    }


    return 0;
}