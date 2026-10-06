/* Задача: Цікаве листування (Алгоритми / Алгостестер)
   Виконав: Сукач Андрій, 
   Група: ШІ-14 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    
    int n;
    if (!(cin >> n)) return 0;

    string s;
    cin >> s;

    int k = sqrt(n); // Оскільки n = k * k

    string result = "";

    // Сума індексів i + j для кожної діагоналі змінюється від 0 до 2k - 2
    for (int d = 0; d <= 2 * k - 2; d++) {
        for (int i = 0; i < k; i++) {
            int j = d - i;
            // Перевіряємо, чи знаходиться j в межах матриці k x k
            if (j >= 0 && j < k) {
                // Символ у матриці з координатами (i, j) знаходиться на позиції i * k + j
                result += s[i * k + j];
            }
        }
    }

    cout << result << "\n";

    return 0;
}