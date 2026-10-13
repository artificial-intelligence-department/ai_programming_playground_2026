/*
* Задача: Веселі каруселі
* Поліщук Вероніка
* Група 14
*/

#include <iostream>

using namespace std;

int main() {
    int k, n;
    cin >> k >> n;

    // масив фіксованого розміру (оскільки n <= 100)
    int c[100];
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    // Сортування бульбашкою за зростанням
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (c[j] > c[j + 1]) {
                // Обмін елементів місцями
                int temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (k >= c[i]) {
            k -= c[i]; // Купуємо квиток на атракціон
            count++;   // Збільшуємо лічильник відвіданих атракціонів
        } else {
            break;     // Грошей більше недостатньо
        }
    }

    cout << count << "\n";

    return 0;
}