
/*
Епік 5. Алготестер 4.2 Варіант 2.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    // Створюємо вектор розміром n та зчитуємо елементи
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Сортуємо вектор за зростанням (необхідно для коректної роботи unique)
    sort(arr.begin(), arr.end());

    // Видаляємо повторювані елементи (ідіома erase-unique)
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    int count = arr.size();

    // Захист від випадків, коли k більше або дорівнює новому розміру масиву
    if (count > 0) k %= count;

    // Циклічний зсув масиву вліво: елемент (arr.begin() + k) стає новим початком
    rotate(arr.begin(), arr.begin() + k, arr.end());

    // Виведення нового розміру множини
    cout << count << endl;

    // Виведення елементів після зсуву
    for (int i = 0; i < count; ++i) {
        cout << arr[i] << ' ';
    }

    return 0;
}
