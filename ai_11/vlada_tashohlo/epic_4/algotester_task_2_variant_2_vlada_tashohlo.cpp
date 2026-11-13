
/* 
Епік 4. Алготестер 2. Варіант 2.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
using namespace std;

int main() {

        int n; // Кількість елементів у масиві
        cin >> n;

        int* r = new int[n]; // Динамічний масив для зберігання елементів

        // Зчитуємо n елементів у масив r
        for (int i = 0; i < n; ++i) {
            cin >> r[i];
        }

    int a, b, c; // Три числа, які потрібно виключити
    cin >> a >> b >> c;

    int* temp = new int[n]; // Тимчасовий масив для елементів, що не дорівнюють a, b, c
    int k = 0; // Лічильник кількості таких елементів

    // Відбираємо елементи, які не дорівнюють a, b або c
    for (int i = 0; i < n; ++i) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            temp[k] = r[i];
            ++k;
        }
    }

    // Створюємо новий масив для сум сусідніх елементів temp
    int* newArr = new int[k > 0 ? k - 1 : 0];

    // Обчислюємо суми сусідніх елементів у temp і записуємо у newArr
    for (int i = 0; i < k - 1; ++i) {
        newArr[i] = temp[i] + temp[i + 1];
    }

    int resultSize = k > 0 ? k - 1 : 0; // Кількість елементів у новому масиві

    cout << resultSize << '\n'; // Виводимо розмір результату

    // Виводимо елементи нового масиву
    for (int i = 0; i < resultSize; ++i) {
        cout << newArr[i] << ' ';
    }

    // Звільняємо пам'ять
    delete[] r;
    delete[] temp;
    delete[] newArr;

    return 0;
}
