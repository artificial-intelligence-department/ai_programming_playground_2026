/*
* Задача: Повторювані числа в матриці
* Поліщук Вероніка
* Група 14
*/
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int total_elements = n * m;

    // Виділяємо пам'ять під елементи матриці
    long long* arr = new long long[total_elements];

    for (int i = 0; i < total_elements; i++) {
        cin >> arr[i];
    }

    // Сортуємо масив, щоб однакові числа стояли поруч
    sort(arr, arr + total_elements);

    // Масив для збереження знайдених дублікатів
    long long* result = new long long[total_elements / 2];
    int count = 0;

    // Проходимо по відсортованому масиву та шукаємо пари
    for (int i = 0; i < total_elements - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            result[count++] = arr[i];
            i++;
        }
    }

    // Виводимо кількість чисел, що зустрічаються рівно 2 рази
    cout << count << endl;

    // Виводим самі числа
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }

    // Звільняємо виділену пам'ять
    delete[] arr;
    delete[] result;
    return 0;
}